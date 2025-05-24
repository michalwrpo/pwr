package main

import (
	"fmt"
	"math/rand"
	"sync"
	"time"
)

const (
	NrOfProcesses = 2

	MinSteps = 50
	MaxSteps = 100

	MinDelay = 10 * time.Millisecond
	MaxDelay = 50 * time.Millisecond

	BoardWidth  = NrOfProcesses
	BoardHeight = 4
)

// for Dekker's algorithm
var C1 int = 1
var C2 int = 1
var Last int = 1

type ProcessState int

const (
	LocalSection ProcessState = iota
	EntryProtocol
	CriticalSection
	ExitProtocol
)

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
		fmt.Printf("LOCAL_SECTION;ENTRY_PROTOCOL;CRITICAL_SECTION;EXIT_PROTOCOL;EXTRA_LABEL;")
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

	StoreTrace(TimeStamp, &process, &traces)

	for range nrOfSteps/4 - 1 {
		// Local Section
		time.Sleep(MinDelay + time.Duration(G.Float64()*float64(MaxDelay-MinDelay)))

		ChangeState(EntryProtocol, StartTime, &process, &traces)
		// Entry Protocol
		if process.ID == 0 {
			C1 = 1
			Last = 1
		} else {
			C2 = 1
			Last = 2
		}

		for {
			if process.ID == 0 {
				if C2 == 0 || Last != 1 {
					break
				}
			} else {
				if C1 == 0 || Last != 2 {
					break
				}
			}
		}

		ChangeState(CriticalSection, StartTime, &process, &traces)
		// Critical Section
		time.Sleep(MinDelay + time.Duration(G.Float64()*float64(MaxDelay-MinDelay)))

		ChangeState(ExitProtocol, StartTime, &process, &traces)
		// Exit Protocol
		if process.ID == 0 {
			C1 = 0
		} else {
			C2 = 0
		}

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
