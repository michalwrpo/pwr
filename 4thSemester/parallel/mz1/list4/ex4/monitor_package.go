package main

import (
	"sync"
)

type Monitor struct {
	enter     chan struct{}
	leave     chan struct{}
	terminate chan struct{}
}

func NewMonitor() *Monitor {
	m := &Monitor{
		enter:     make(chan struct{}),
		leave:     make(chan struct{}),
		terminate: make(chan struct{}),
	}
	go m.run()
	return m
}

func (m *Monitor) run() {
	for {
		select {
		case <-m.enter:
		case <-m.terminate:
			return
		}

		select {
		case <-m.leave:
		case <-m.terminate:
			return
		}
	}
}

func (m *Monitor) Enter() {
	m.enter <- struct{}{}
}

func (m *Monitor) Leave() {
	m.leave <- struct{}{}
}

func (m *Monitor) Stop() {
	m.terminate <- struct{}{}
	close(m.terminate)
	close(m.enter)
	close(m.leave)
}

type Condition struct {
	monitor   *Monitor
	signal    chan struct{}
	preWait   chan chan struct{}
	waiting   chan chan bool
	terminate chan struct{}
	count     int
	mu        sync.Mutex
}

func NewCondition(m *Monitor) *Condition {
	c := &Condition{
		monitor:   m,
		signal:    make(chan struct{}),
		preWait:   make(chan chan struct{}),
		waiting:   make(chan chan bool),
		terminate: make(chan struct{}),
		count:     0,
	}
	go c.run()
	return c
}

func (c *Condition) run() {
	queue := make([]chan struct{}, 0)
	for {
		select {
		case <-c.signal:
			c.mu.Lock()
			if c.count == 0 {
				c.monitor.Leave()
			} else {
				c.count--
				ch := queue[0]
				queue = queue[1:]
				ch <- struct{}{}
			}
			c.mu.Unlock()
		case ch := <-c.preWait:
			c.mu.Lock()
			queue = append(queue, ch)
			c.count++
			c.mu.Unlock()
		case ch := <-c.waiting:
			c.mu.Lock()
			ch <- c.count != 0
			c.mu.Unlock()
		case <-c.terminate:
			return
		}
	}
}

func (c *Condition) Signal() {
	c.signal <- struct{}{}
}

func (c *Condition) PreWait() chan struct{} {
	ch := make(chan struct{})
	c.preWait <- ch
	return ch
}

func (c *Condition) Waiting() bool {
	ch := make(chan bool)
	c.waiting <- ch
	return <-ch
}

func (c *Condition) Stop() {
	c.terminate <- struct{}{}
	close(c.signal)
	close(c.waiting)
	close(c.preWait)
	close(c.terminate)
}

func NonEmpty(c *Condition) bool {
	return c.Waiting()
}

func Wait(c *Condition) struct{} {
	ch := c.PreWait()
	c.monitor.Leave()
	return <-ch
}
