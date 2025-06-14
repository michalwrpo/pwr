package main

import (
	"sync"
)

type RWMonitor struct {
	monitor   *Monitor
	okToRead  *Condition
	okToWrite *Condition
	readers   int
	writing   bool
	stateMu   sync.Mutex
}

func NewRWMonitor() *RWMonitor {
	m := NewMonitor()
	return &RWMonitor{
		monitor:   m,
		okToRead:  NewCondition(m),
		okToWrite: NewCondition(m),
		readers:   0,
		writing:   false,
	}
}

func (rw *RWMonitor) StartRead() {
	rw.monitor.Enter()

	rw.stateMu.Lock()
	wait := rw.writing || NonEmpty(rw.okToWrite)

	if wait {
		rw.stateMu.Unlock()
		Wait(rw.okToRead)
	} else {
		rw.stateMu.Unlock()
	}

	rw.stateMu.Lock()
	rw.readers++
	rw.stateMu.Unlock()

	rw.okToRead.Signal()
}

func (rw *RWMonitor) StopRead() {
	rw.monitor.Enter()

	rw.stateMu.Lock()
	rw.readers--
	isLastReader := rw.readers == 0

	if isLastReader {
		rw.stateMu.Unlock()
		rw.okToWrite.Signal()
	} else {
		rw.stateMu.Unlock()
		rw.monitor.Leave()
	}
}

func (rw *RWMonitor) StartWrite() {
	rw.monitor.Enter()

	rw.stateMu.Lock()
	wait := rw.readers != 0 || rw.writing

	if wait {
		rw.stateMu.Unlock()
		Wait(rw.okToWrite)
	} else {
		rw.stateMu.Unlock()
	}

	rw.stateMu.Lock()
	rw.writing = true
	rw.stateMu.Unlock()

	rw.monitor.Leave()
}

func (rw *RWMonitor) StopWrite() {
	rw.monitor.Enter()

	rw.stateMu.Lock()
	rw.writing = false
	nonEmpty := NonEmpty(rw.okToRead)

	if nonEmpty {
		rw.stateMu.Unlock()
		rw.okToRead.Signal()
	} else {
		rw.stateMu.Unlock()
		rw.okToWrite.Signal()
	}
}
