import re
import sys
import time

sys.setrecursionlimit(3000)

def flow(grid, x, y, d):
    if grid[y][x] == '.':
        grid[y][x] = '|'
    if y == len(grid) - 1:
        return
    if grid[y][x] == '#':
        return x
    if grid[y+1][x] == '.':
        flow(grid, x, y+1, 0)
    if grid[y+1][x] in '~#':
        if d:
            return flow(grid, x+d, y, d)
        else:
            leftX = flow(grid, x-1, y, -1)
            rightX = flow(grid, x+1, y, 1)
            if grid[y][leftX] == '#' and grid[y][rightX] == '#':
                for fillX in xrange(leftX+1, rightX):
                    grid[y][fillX] = '~'
    else:
        return x

def solve(filename):
    data = []
    for line in open(filename).read().splitlines():
        a, b, c = map(int, re.findall('\d+', line))
        data += [(a, a, b, c)] if line[0] == 'x' else [(b, c, a, a)]

    Z = zip(*data)
    minX, maxX, minY, maxY = min(Z[0]), max(Z[1]), min(Z[2]), max(Z[3])

    grid = [['.']*(maxX - minX + 2) for _ in xrange(maxY + 1)]
    for x1, x2, y1, y2 in data:
        for x in xrange(x1, x2 + 1):
            for y in xrange(y1, y2 + 1):
                grid[y][x - minX + 1] = '#'
    springX, springY = 500 - minX + 1, 0
    grid[0][springX] = '+'

    flow(grid, springX, springY, 0)

    still = flowing = 0
    for y in xrange(minY, maxY + 1):
        for x in xrange(len(grid[0])):
            if grid[y][x] == '|':
                flowing += 1
            elif grid[y][x] == '~':
                still += 1
                
    f = open('pyoutput.txt', 'w')
    for r in range(len(grid)):
        for c in range(len(grid[0])):
            f.write(grid[r][c]);
        f.write('\n')
    f.close()

    return still + flowing, still

startTime = time.time()
ans1, ans2 = solve('input.txt')
endTime = time.time()
print '\nfinished in %.6f sec' % (endTime - startTime)
print 'ans (part 1): ' + str(ans1)
print 'ans (part 2): ' + str(ans2)