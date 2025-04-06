package main

import (
	"math/rand"
	"time"
)

// GenerateSeeds generates random seeds for travelers
func GenerateSeeds(size int) []int {
	r := rand.New(rand.NewSource(time.Now().UnixNano()))
	seeds := make([]int, size)
	for i := range seeds {
		seeds[i] = r.Intn(1e6)
	}
	return seeds
}
