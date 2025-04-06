package main

import (
	"fmt"
	"math"
	"math/rand"
	"sync"
	"time"
)

// Constants
const (
	NrOfTravelers = 15
	MinSteps      = 10
	MaxSteps      = 100
	MinDelay      = 10 * time.Millisecond
	MaxDelay      = 50 * time.Millisecond
	BoardWidth    = 15
	BoardHeight   = 15
)

// Position represents a 2D position on the board
type Position struct {
	X int
	Y int
}

// Trace represents a traveler's trace information
type Trace struct {
	TimeStamp time.Duration
	ID        int
	Position  Position
	Symbol    rune
}

// TraceSequence stores traces for a traveler
type TraceSequence struct {
	Last       int
	TraceArray [MaxSteps + 1]Trace
}

// Traveler represents a traveler on the board
type Traveler struct {
	ID       int
	Symbol   rune
	Position Position
}

// Printer task to collect and print traces
type Printer struct {
	mu sync.Mutex
}

// Method to print a single trace
func (p *Printer) PrintTrace(trace Trace) {
	fmt.Printf("%f  %d  %d  %d  %c\n", float64(trace.TimeStamp.Microseconds())/(math.Pow(10, 6)), trace.ID, trace.Position.X, trace.Position.Y, trace.Symbol)
}

// Method to print all traces
func (p *Printer) PrintTraces(traces TraceSequence) {
	for i := 0; i <= traces.Last; i++ {
		p.PrintTrace(traces.TraceArray[i])
	}
}

// Function to move up
func MoveUp(position *Position) {
	position.Y = (position.Y + BoardHeight - 1) % BoardHeight
}

// Function to move down
func MoveDown(position *Position) {
	position.Y = (position.Y + 1) % BoardHeight
}

// Function to move left
func MoveLeft(position *Position) {
	position.X = (position.X + BoardWidth - 1) % BoardWidth
}

// Function to move right
func MoveRight(position *Position) {
	position.X = (position.X + 1) % BoardWidth
}

// Function for a traveler to make a step
func (t *Traveler) MakeStep() {
	moveDirection := rand.Intn(4)
	switch moveDirection {
	case 0:
		MoveUp(&t.Position)
	case 1:
		MoveDown(&t.Position)
	case 2:
		MoveLeft(&t.Position)
	case 3:
		MoveRight(&t.Position)
	}
}

// Traveler task
func TravelerTask(id, seed int, symbol rune, StartTime time.Time, printer *Printer) {
	G := rand.New(rand.NewSource(time.Now().UnixNano()))
	traveler := Traveler{
		ID:       id,
		Symbol:   symbol,
		Position: Position{X: G.Intn(BoardWidth), Y: G.Intn(BoardHeight)},
	}
	traces := TraceSequence{Last: -1}

	// Store the starting position
	traces.Last++
	traces.TraceArray[traces.Last] = Trace{
		TimeStamp: time.Duration(0),
		ID:        traveler.ID,
		Position:  traveler.Position,
		Symbol:    traveler.Symbol,
	}

	// Number of steps to take
	nrOfSteps := MinSteps + rand.Intn(MaxSteps-MinSteps)
	TimeStamp := time.Now().Sub(StartTime)

	for range nrOfSteps {
		time.Sleep(MinDelay + time.Duration((float64(MaxDelay)-float64(MinDelay))*G.Float64()))
		traveler.MakeStep()

		// Store trace after the step
		traces.Last++
		traces.TraceArray[traces.Last] = Trace{
			TimeStamp: TimeStamp,
			ID:        traveler.ID,
			Position:  traveler.Position,
			Symbol:    traveler.Symbol,
		}
		TimeStamp = time.Now().Sub(StartTime)
	}

	// Report traces after completing the steps
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

	// Start traveler tasks
	var wg sync.WaitGroup
	for i := range NrOfTravelers {
		wg.Add(1)
		go func(id int, seed int, symbol rune) {
			defer wg.Done()
			TravelerTask(id, seed, symbol, StartTime, printer)
		}(i, seeds[i], rune('A'+i))
	}

	// Wait for all traveler tasks to complete
	wg.Wait()
}
