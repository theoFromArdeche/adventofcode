package main

import ("bufio"; "fmt"; "os"; "strconv")



func abs(x int) int {
	if (x < 0) {
		return -x
	}
	return x
}


func boolToInt(b bool) int {
    if (b) {
        return 1
    }
    return 0
}


func day9(importantKnot int) int {
	file, err := os.Open("input.txt")
	if err != nil {
		fmt.Println("Error opening file:", err)
		return -1
	}
	defer file.Close()

	grid := make([][]bool, 1000)
	for i := range grid {
		grid[i] = make([]bool, 1000)
	}

	directions := map[string][]int{"L": {-1, 0}, "R": {1, 0}, "U": {0, -1}, "D": {0, 1}}

	knotsCoords := make([][]int, importantKnot+1)
	for i := range knotsCoords {
		knotsCoords[i] = []int{500, 500}
	}

	grid[knotsCoords[importantKnot][1]][knotsCoords[importantKnot][0]] = true
	solution := 1

	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		line := scanner.Text()
		count, _ := strconv.Atoi(line[2:])

		for steps := 0; steps < count; steps++ {
			deltaX := directions[string(line[0])][0]
			deltaY := directions[string(line[0])][1]

			knotsCoords[0][0] += deltaX
			knotsCoords[0][1] += deltaY

			for i := 1; i <= importantKnot; i++ {
				if (abs(knotsCoords[i-1][0]-knotsCoords[i][0]) > 1 || abs(knotsCoords[i-1][1]-knotsCoords[i][1]) > 1) {
					deltaX := boolToInt(knotsCoords[i-1][0] > knotsCoords[i][0]) - boolToInt(knotsCoords[i-1][0] < knotsCoords[i][0])
					deltaY := boolToInt(knotsCoords[i-1][1] > knotsCoords[i][1]) - boolToInt(knotsCoords[i-1][1] < knotsCoords[i][1])
					knotsCoords[i][0] += deltaX
					knotsCoords[i][1] += deltaY
				} else {
					break
				}
			}

			if (!grid[knotsCoords[importantKnot][1]][knotsCoords[importantKnot][0]]) {
				grid[knotsCoords[importantKnot][1]][knotsCoords[importantKnot][0]] = true
				solution++
			}
		}
	}

	return solution
}



func main() {
	fmt.Println("Part 1 solution:", day9(1))
	fmt.Println("Part 2 solution:", day9(9))
}