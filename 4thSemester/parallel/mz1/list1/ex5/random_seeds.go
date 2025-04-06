package main

import (
	"time"
)

// GenerateSeeds generates random seeds for travelers
func GenerateSeeds(n int) []int64 {
	seeds := make([]int64, n)
	for i := range seeds {
		seeds[i] = time.Now().UnixNano() + int64(i*1000)
	}
	return seeds
}
