package main

import (
	"fmt"
	"math/rand"
	"sync"
	"time"
)

const (
	NrOfReaders   = 10
	NrOfWriters   = 5
	NrOfProcesses = NrOfReaders + NrOfWriters

	MinSteps = 50
	MaxSteps = 100

	MinDelay = 10 * time.Millisecond
	MaxDelay = 50 * time.Millisecond

	BoardWidth  = NrOfProcesses
	BoardHeight = 4
)

type ProcessState int

const (
	LocalSection ProcessState = iota
	Start
	ReadingRoom
	Stop
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
		fmt.Printf("LOCAL_SECTION;START;READING_ROOM;STOP;EXTRA_LABEL;")
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

func ReaderTask(id int, seed int64, StartTime time.Time, printer *Printer, rw *RWMonitor) {
	G := rand.New(rand.NewSource(seed))
	process := Process{
		ID:       id,
		Symbol:   'R',
		Position: Position{X: id, Y: int(LocalSection)},
	}
	traces := TraceSequence{Last: -1}

	nrOfSteps := MinSteps + G.Intn(MaxSteps-MinSteps)
	TimeStamp := time.Since(StartTime)

	StoreTrace(TimeStamp, &process, &traces)

	for range nrOfSteps/4 - 1 {
		// Local Section
		time.Sleep(MinDelay + time.Duration(G.Float64()*float64(MaxDelay-MinDelay)))

		ChangeState(Start, StartTime, &process, &traces)
		// Entry Protocol
		rw.StartRead()

		ChangeState(ReadingRoom, StartTime, &process, &traces)
		// Critical Section
		time.Sleep(MinDelay + time.Duration(G.Float64()*float64(MaxDelay-MinDelay)))

		ChangeState(Stop, StartTime, &process, &traces)
		// Exit Protocol
		rw.StopRead()

		ChangeState(LocalSection, StartTime, &process, &traces)
	}

	printer.PrintTraces(traces)
}

func WriterTask(id int, seed int64, StartTime time.Time, printer *Printer, rw *RWMonitor) {
	G := rand.New(rand.NewSource(seed))
	process := Process{
		ID:       id,
		Symbol:   'W',
		Position: Position{X: id, Y: int(LocalSection)},
	}
	traces := TraceSequence{Last: -1}

	nrOfSteps := MinSteps + G.Intn(MaxSteps-MinSteps)
	TimeStamp := time.Since(StartTime)

	StoreTrace(TimeStamp, &process, &traces)

	for range nrOfSteps/4 - 1 {
		// Local Section
		time.Sleep(MinDelay + time.Duration(G.Float64()*float64(MaxDelay-MinDelay)))

		ChangeState(Start, StartTime, &process, &traces)
		// Entry Protocol
		rw.StartWrite()

		ChangeState(ReadingRoom, StartTime, &process, &traces)
		// Critical Section
		time.Sleep(MinDelay + time.Duration(G.Float64()*float64(MaxDelay-MinDelay)))

		ChangeState(Stop, StartTime, &process, &traces)
		// Exit Protocol
		rw.StopWrite()

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

	// Initialize the RWMonitor task
	rw := NewRWMonitor()

	// Start traveler tasks
	var wg sync.WaitGroup
	for i := range NrOfReaders {
		wg.Add(1)
		go func(id int, seed int64) {
			defer wg.Done()
			ReaderTask(id, seed, StartTime, printer, rw)
		}(i, seeds[i])
	}

	for i := range NrOfWriters {
		wg.Add(1)
		go func(id int, seed int64) {
			defer wg.Done()
			WriterTask(id, seed, StartTime, printer, rw)
		}(i+NrOfReaders, seeds[i+NrOfReaders])
	}

	// Wait for all traveler tasks to complete
	wg.Wait()
}
