package main

import (
	"fmt"
	"math/rand"
	"sync"
	"time"
)

const (
	NrOfTravelers = 15
	MinSteps      = 10
	MaxSteps      = 100
	MinDelay      = 10 * time.Millisecond
	MaxDelay      = 50 * time.Millisecond
	BoardWidth    = 15
	BoardHeight   = 15
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

type Traveler struct {
	ID       int
	Symbol   rune
	Position Position
}

type Field struct {
	mu sync.Mutex
}

func (f *Field) TryTake(timeout time.Duration) bool {
	timer := time.NewTimer(timeout)
	defer timer.Stop()
	ch := make(chan bool, 1)
	go func() {
		f.mu.Lock()
		ch <- true
	}()
	select {
	case <-ch:
		return true
	case <-timer.C:
		return false
	}
}

var Board [BoardWidth][BoardHeight]*Field

func Move(position *Position, dx, dy int) bool {
	newX := (position.X + dx + BoardWidth) % BoardWidth
	newY := (position.Y + dy + BoardHeight) % BoardHeight
	if Board[newX][newY].TryTake(3 * MaxDelay) {
		Board[position.X][position.Y].mu.Unlock()
		position.X = newX
		position.Y = newY
		return true
	}
	return false
}

func (p *Printer) PrintTrace(trace Trace) {
	fmt.Printf("%f  %d  %d  %d  %c\n", float64(trace.TimeStamp.Microseconds())/1e6, trace.ID, trace.Position.X, trace.Position.Y, trace.Symbol)
}

func (p *Printer) PrintTraces(traces TraceSequence) {
	for i := 0; i <= traces.Last; i++ {
		p.PrintTrace(traces.TraceArray[i])
	}
}

type Printer struct {
	mu sync.Mutex
}

func TravelerTask(id int, seed int64, symbol rune, StartTime time.Time, printer *Printer) {
	G := rand.New(rand.NewSource(seed))
	traveler := Traveler{ID: id, Symbol: symbol}
	traces := TraceSequence{Last: -1}
	traveler.Position = Position{X: id, Y: id}
	Board[id][id].TryTake(3 * MaxDelay)
	moveDir := 2*(id%2) + G.Intn(2)

	traces.Last++
	traces.TraceArray[traces.Last] = Trace{
		TimeStamp: time.Duration(0),
		ID:        traveler.ID,
		Position:  traveler.Position,
		Symbol:    traveler.Symbol,
	}

	nrOfSteps := MinSteps + G.Intn(MaxSteps-MinSteps)
	TimeStamp := time.Since(StartTime)

	for range nrOfSteps {
		time.Sleep(MinDelay + time.Duration(G.Float64()*float64(MaxDelay-MinDelay)))
		success := false
		switch moveDir {
		case 0:
			success = Move(&traveler.Position, 0, -1)
		case 1:
			success = Move(&traveler.Position, 0, 1)
		case 2:
			success = Move(&traveler.Position, -1, 0)
		case 3:
			success = Move(&traveler.Position, 1, 0)
		}
		TimeStamp = time.Since(StartTime)
		if !success {
			traveler.Symbol = rune(symbol + 32) // mark as failed
			traces.Last++
			traces.TraceArray[traces.Last] = Trace{
				TimeStamp: TimeStamp,
				ID:        traveler.ID,
				Position:  traveler.Position,
				Symbol:    traveler.Symbol,
			}
			break
		}
		traces.Last++
		traces.TraceArray[traces.Last] = Trace{
			TimeStamp: TimeStamp,
			ID:        traveler.ID,
			Position:  traveler.Position,
			Symbol:    traveler.Symbol,
		}
	}

	printer.PrintTraces(traces)
}

func main() {
	StartTime := time.Now()
	// Generate random seeds for each traveler
	seeds := GenerateSeeds(NrOfTravelers)

	// Initialize the printer task
	printer := &Printer{}

	// Initialize trace storage
	fmt.Printf("-1 %d %d %d\n", NrOfTravelers, BoardWidth, BoardHeight)

	for x := range BoardWidth {
		for y := range BoardHeight {
			Board[x][y] = &Field{}
		}
	}

	// Start traveler tasks
	var wg sync.WaitGroup
	for i := range NrOfTravelers {
		wg.Add(1)
		go func(id int, seed int64, symbol rune) {
			defer wg.Done()
			TravelerTask(id, seed, symbol, StartTime, printer)
		}(i, seeds[i], rune('A'+i))
	}

	// Wait for all traveler tasks to complete
	wg.Wait()
}
