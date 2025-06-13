package main

import (
	"fmt"
	"math/rand"
	"sync"
	"time"
)

const (
	NrOfProcesses = 15

	MinSteps = 50
	MaxSteps = 100

	MinDelay = 10 * time.Millisecond
	MaxDelay = 50 * time.Millisecond

	BoardWidth  = NrOfProcesses
	BoardHeight = 7
)

type ProcessState int

const (
	LocalSection ProcessState = iota
	EntryProtocol1
	EntryProtocol2
	EntryProtocol3
	EntryProtocol4
	CriticalSection
	ExitProtocol
)

var Flags = [NrOfProcesses]int{}

type Position struct {
	X int
	Y int
}

type Trace struct {
	TimeStamp time.Duration
	ID        int
	Position  Position
	Symbol    rune
}

type TraceSequence struct {
	Last       int
	TraceArray [MaxSteps + 1]Trace
}

func (p *Printer) PrintTrace(trace Trace) {
	fmt.Printf("%.9f  %d  %d  %d  %c\n", float64(trace.TimeStamp.Nanoseconds())/1e9, trace.ID, trace.Position.X, trace.Position.Y, trace.Symbol)
}

func (p *Printer) PrintTraces(traces TraceSequence) {
	for i := 0; i <= traces.Last; i++ {
		p.PrintTrace(traces.TraceArray[i])
	}
	p.ReturnedTraces++

	if p.ReturnedTraces == NrOfProcesses {
		fmt.Printf("-1 %d %d %d ", NrOfProcesses, BoardWidth, BoardHeight)
		fmt.Printf("LOCAL_SECTION;ENTRY_PROTOCOL_1;ENTRY_PROTOCOL_2;ENTRY_PROTOCOL_3;ENTRY_PROTOCOL_4;CRITICAL_SECTION;EXIT_PROTOCOL;EXTRA_LABEL;")
	}
}

type Printer struct {
	ReturnedTraces int
}

type Process struct {
	ID       int
	Symbol   rune
	Position Position
}

func StoreTrace(timeStamp time.Duration, process *Process, traces *TraceSequence) {
	traces.Last++
	traces.TraceArray[traces.Last] = Trace{
		TimeStamp: timeStamp,
		ID:        process.ID,
		Position:  process.Position,
		Symbol:    process.Symbol,
	}
}

func ChangeState(state ProcessState, StartTime time.Time, process *Process, traces *TraceSequence) {
	timeStamp := time.Since(StartTime)
	process.Position.Y = int(state)
	StoreTrace(timeStamp, process, traces)
}

func ProcessTask(id int, seed int64, symbol rune, StartTime time.Time, printer *Printer) {
	G := rand.New(rand.NewSource(seed))
	process := Process{
		ID:       id,
		Symbol:   symbol,
		Position: Position{X: id, Y: int(LocalSection)},
	}
	traces := TraceSequence{Last: -1}

	nrOfSteps := MinSteps + G.Intn(MaxSteps-MinSteps)
	TimeStamp := time.Since(StartTime)
	condition := false

	StoreTrace(TimeStamp, &process, &traces)

	for range nrOfSteps/7 - 1 {
		// Local Section
		time.Sleep(MinDelay + time.Duration(G.Float64()*float64(MaxDelay-MinDelay)))

		ChangeState(EntryProtocol1, StartTime, &process, &traces)
		// Entry Protocol
		Flags[id] = 1
		condition = false
		for !condition {
			condition = true
			for i := range NrOfProcesses {
				if Flags[i] > 2 {
					condition = false
					break
				}
			}
		}

		Flags[id] = 3
		ChangeState(EntryProtocol2, StartTime, &process, &traces)

		for i := range NrOfProcesses {
			if Flags[i] == 1 {
				Flags[id] = 2
				ChangeState(EntryProtocol3, StartTime, &process, &traces)

				condition = false
				for !condition {
					for i := range NrOfProcesses {
						if Flags[i] == 4 {
							condition = true
							break
						}
					}
				}
				break
			}
		}

		Flags[id] = 4
		ChangeState(EntryProtocol4, StartTime, &process, &traces)

		condition = false
		for !condition {
			condition = true
			for i := range id {
				if Flags[i] > 1 {
					condition = false
					break
				}
			}
		}

		ChangeState(CriticalSection, StartTime, &process, &traces)
		// Critical Section
		time.Sleep(MinDelay + time.Duration(G.Float64()*float64(MaxDelay-MinDelay)))

		ChangeState(ExitProtocol, StartTime, &process, &traces)
		// Exit Protocol
		condition = false
		for !condition {
			condition = true
			for i := id + 1; i < NrOfProcesses; i++ {
				if Flags[i] == 2 || Flags[i] == 3 {
					condition = false
					break
				}
			}
		}

		Flags[id] = 0
		ChangeState(LocalSection, StartTime, &process, &traces)
	}

	printer.PrintTraces(traces)
}

func main() {
	StartTime := time.Now()
	// Generate random seeds for each traveler
	seeds := GenerateSeeds(NrOfProcesses)

	// Initialize the printer task
	printer := &Printer{0}

	// Start traveler tasks
	var wg sync.WaitGroup
	for i := range NrOfProcesses {
		wg.Add(1)
		go func(id int, seed int64, symbol rune) {
			defer wg.Done()
			ProcessTask(id, seed, symbol, StartTime, printer)
		}(i, seeds[i], rune('A'+i))
	}

	// Wait for all traveler tasks to complete
	wg.Wait()
}
