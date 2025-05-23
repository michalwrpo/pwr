package main

import (
	"fmt"
	"math/rand"
	"sync"
	"time"
)

const (
	NrOfTravelers = 15
	MaxOccupants  = 10
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
	mu         sync.Mutex
	byTraveler bool
	occupant   *Occupant
}

func (f *Field) TryTake(byTraveler bool, timeout time.Duration) bool {
	timer := time.NewTimer(timeout)
	defer timer.Stop()
	ch := make(chan bool, 1)
	go func() {
		f.mu.Lock()
		f.byTraveler = byTraveler
		ch <- true
	}()
	select {
	case success := <-ch:
		return success
	case <-timer.C:
		return false
	}
}

func (f *Field) Free() {
	f.byTraveler = true
	f.occupant = nil
	f.mu.Unlock()
}

func (f *Field) OccupantPresent() bool {
	return f.occupant != nil
}

var Board [BoardWidth][BoardHeight]*Field

type OccupantIDType struct {
	ID int
	mu sync.Mutex
}

func (O *OccupantIDType) Get() int {
	O.mu.Lock()
	id := -1
	if O.ID < NrOfTravelers+MaxOccupants {
		id = O.ID
		O.ID += 1
	}
	O.mu.Unlock()
	return id
}

var OccupantID OccupantIDType = OccupantIDType{
	ID: NrOfTravelers,
}

func FieldTask(x, y int, startTime time.Time, printer *Printer) {
	g := rand.New(rand.NewSource(time.Now().UnixNano()))

	for {
		select {
		case <-time.After(time.Duration(g.Intn(100)) * time.Millisecond):
			if g.Intn(100) == 0 {
				field := Board[x][y]
				if field.TryTake(false, 10*time.Millisecond) {
					id := OccupantID.Get()
					if id > 0 {
						occ := &Occupant{
							ID:       id,
							Symbol:   rune('0' + id%10),
							Position: Position{X: x, Y: y},
							Lifespan: time.Duration(100+g.Intn(900)) * time.Millisecond,
							move:     make(chan bool),
						}
						field.occupant = occ
						go occ.Run(startTime, printer)
					}
				}
			}
		}
	}
}

type Occupant struct {
	ID       int
	Symbol   rune
	Position Position
	Lifespan time.Duration
	move     chan bool
}

func (O *Occupant) Run(startTime time.Time, printer *Printer) {
	ticker := time.NewTicker(40 * time.Millisecond)
	defer ticker.Stop()
	timeout := time.After(O.Lifespan)

	traces := TraceSequence{Last: -1}
	recordTrace := func() {
		now := time.Since(startTime)
		traces.Last++
		traces.TraceArray[traces.Last] = Trace{
			TimeStamp: now,
			ID:        O.ID,
			Position:  O.Position,
			Symbol:    O.Symbol,
		}
	}

	recordTrace()

	for {
		select {
		case <-ticker.C:
			recordTrace()
			continue
		case <-timeout:
			Board[O.Position.X][O.Position.Y].Free()
			O.Symbol = '.'
			recordTrace()
			printer.PrintTraces(traces)
			return
		case <-O.move:
			moveDirs := []Position{{0, -1}, {0, 1}, {-1, 0}, {1, 0}}
			var newX, newY int
			for _, move := range moveDirs {
				newX = (O.Position.X + move.X + BoardWidth) % BoardWidth
				newY = (O.Position.Y + move.Y + BoardHeight) % BoardHeight

				if Board[newX][newY].TryTake(false, 5*time.Millisecond) {
					Board[O.Position.X][O.Position.Y].Free()
					O.Position.X = newX
					O.Position.Y = newY
					recordTrace()
					break
				}
			}
		}
	}
}

func MoveTraveler(position *Position, dx, dy int) bool {
	newX := (position.X + dx + BoardWidth) % BoardWidth
	newY := (position.Y + dy + BoardHeight) % BoardHeight

	field := Board[newX][newY]

	if field.OccupantPresent() {
		// Try to move occupant
		field.occupant.move <- true
		time.Sleep(50 * time.Millisecond) // give some time for occupant to move
	}

	if field.TryTake(true, 3*MaxDelay) {
		Board[position.X][position.Y].Free()
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

	tryLimit := 1000
	for tries := range tryLimit {
		x := G.Intn(BoardWidth)
		y := G.Intn(BoardHeight)
		if Board[x][y].TryTake(true, 1*time.Millisecond) {
			traveler.Position = Position{X: x, Y: y}
			break
		} else if tries == tryLimit-1 {
			traveler.Symbol = rune(symbol + 32) // lower-case
			printer.PrintTraces(traces)
			return
		}
	}

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
		moveDir := G.Intn(4)
		success := false
		switch moveDir {
		case 0:
			success = MoveTraveler(&traveler.Position, 0, -1)
		case 1:
			success = MoveTraveler(&traveler.Position, 0, 1)
		case 2:
			success = MoveTraveler(&traveler.Position, -1, 0)
		case 3:
			success = MoveTraveler(&traveler.Position, 1, 0)
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
	fmt.Printf("-1 %d %d %d\n", NrOfTravelers+MaxOccupants, BoardWidth, BoardHeight)

	for x := range BoardWidth {
		for y := range BoardHeight {
			Board[x][y] = &Field{}
			go FieldTask(x, y, StartTime, printer)
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
