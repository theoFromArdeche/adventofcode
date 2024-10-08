
def main(cmp, cnd):
    file = open("input.txt")
    grid = [list(line.strip()) for line in file.readlines()]
    selected = [[0 for _ in range(len(grid[0]))] for _ in range(len(grid))]

    solutionPart1 = len(grid)*2 + len(grid[0])*2 - 4
    solutionPart2 = 1
    rowMaxTop = list([[[c, 0]] for c in grid[0]]) # list of stacks of [value, index]
    rowMaxBottom = list([[[c, len(grid)-1]] for c in grid[-1]]) # list of stacks of [value, index]
    for row in range(1, len(grid)-1):
        leftMax = [[grid[row][0], 0]] # stack of [value, index]
        rightMax = [[grid[row][-1], len(grid[0])-1]] # stack of [value, index]
        for column in range(1, len(grid[0])-1):
            if cmp(grid[row][column], cnd(leftMax)) or cmp(grid[row][column], cnd(rowMaxTop[column])):
                while leftMax and grid[row][column] > leftMax[-1][0]:
                    leftMax.pop()
                if (not leftMax): leftMax = [[grid[row][column], 0]]

                while rowMaxTop[column] and grid[row][column] > rowMaxTop[column][-1][0]:
                    rowMaxTop[column].pop()
                if (not rowMaxTop[column]): rowMaxTop[column] = [[grid[row][column], 0]]

                if (selected[row][column] == 0):
                    selected[row][column] = 1
                    solutionPart1+=1
                selected[row][column] *= (column - leftMax[-1][1]) * (row - rowMaxTop[column][-1][1])
                solutionPart2 = max(solutionPart2, selected[row][column])

                leftMax.append([grid[row][column], column])
                rowMaxTop[column].append([grid[row][column], row])

            if cmp(grid[row][-1-column], cnd(rightMax)):
                while rightMax and grid[row][-1-column] > rightMax[-1][0]:
                    rightMax.pop()
                if (not rightMax): rightMax = [[grid[row][-1-column], len(grid[0])-1]]
                
                if (selected[row][-1-column] == 0):
                    selected[row][-1-column] = 1
                    solutionPart1+=1
                selected[row][-1-column] *= rightMax[-1][1] - (len(grid[0]) - 1 - column)
                solutionPart2 = max(solutionPart2, selected[row][-1-column])

                rightMax.append([grid[row][-1-column], len(grid[0])-1-column])

            if cmp(grid[-1-row][column], cnd(rowMaxBottom[column])):
                while rowMaxBottom[column] and grid[-1-row][column] > rowMaxBottom[column][-1][0]:
                    rowMaxBottom[column].pop()
                if (not rowMaxBottom[column]): rowMaxBottom[column] = [[grid[-1-row][column], len(grid)-1]]

                if (selected[-1-row][column] == 0):
                    selected[-1-row][column] = 1
                    solutionPart1+=1
                selected[-1-row][column] *= rowMaxBottom[column][-1][1] - (len(grid)-1-row)
                solutionPart2 = max(solutionPart2, selected[-1-row][column])

                rowMaxBottom[column].append([grid[-1-row][column], len(grid)-1-row])

    file.close()
    return [solutionPart1, solutionPart2]


print("Part 1 solution:", main(lambda a, b : a > b, lambda a : a[0][0])[0])
print("Part 2 solution:", main(lambda a, b : True, lambda a : a[-1][0])[1])
