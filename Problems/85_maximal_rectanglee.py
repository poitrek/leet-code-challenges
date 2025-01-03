from numpy import array


class Solution_Else_1:
    """another solution shown on leetcode - inspired my 2nd solution"""
    def maximalRectangle(self, matrix: list[list[str]]) -> int:
        if not matrix or not matrix[0]:
            return 0
        print(array(matrix))
        n = len(matrix[0])
        height = [0] * (n + 1)
        ans = 0

        for row in matrix:
            for i in range(n):
                height[i] = height[i] + 1 if row[i] == '1' else 0

            stack = [-1]
            for i in range(n + 1):
                while height[i] < height[stack[-1]]:
                    h = height[stack.pop()]
                    w = i - 1 - stack[-1]
                    ans = max(ans, h * w)
                stack.append(i)

        return ans


class Solution:
    """First idea. Memorize widths/heights of "maximum rectangle candidates" for all cells
    in previous row. Space complexity: O(N*N) for N columns"""
    def maximalRectangle(self, matrix: list[list[str]]) -> int:
        # print(matrix)
        matrix = list(map(lambda arr: list(map(int, arr)), matrix))
        # print(matrix)
        print(array(matrix))
        n = len(matrix)
        m = len(matrix[0])
        d = [dict() for _ in range(m)]
        max_area = 0
        # Process 0th line
        one_streak = 0
        for col_no in range(m):
            if matrix[0][col_no] == 0:
                one_streak = 0
            else:
                one_streak += 1
                d[col_no][one_streak] = 1
                area = one_streak
                if area > max_area:
                    max_area = area
        print(d)
        # Process the rest of lines
        for line_no in range(1, n):
            d_new = [dict() for _ in range(m)]
            one_streak = 0
            for col_no in range(m):
                if matrix[line_no][col_no] == 1:
                    one_streak += 1
                    if matrix[line_no - 1][col_no] == 1:
                        d_prev_cell = d[col_no]
                        d_cur_cell = d_new[col_no]
                        for width in d_prev_cell.keys():
                            if width > one_streak:
                                break
                            # set "depth" (length of the maximum rectangle for this width) as previous plus one
                            depth = d_prev_cell[width] + 1
                            d_new[col_no][width] = depth
                            max_area = max(width * depth, max_area)
                        area = 0
                        if width < one_streak:
                            d_cur_cell[one_streak] = 1
                            area = one_streak
                        elif one_streak not in d_cur_cell:
                            d_cur_cell[one_streak] = d_prev_cell[width] + 1
                            area = one_streak * d_cur_cell[one_streak]
                        max_area = max(area, max_area)
                    else:
                        d_new[col_no][one_streak] = 1
                        max_area = max(one_streak, max_area)
                else:
                    one_streak = 0
            d = d_new
            print(d_new)
        return max_area


class Solution2:
    """Smaller space complexity, O(max(M, N)) for a M*N array. For each row, memorizes only heights
    and widths of all "maximum rectangle candidates" of previous cell, to find them for current
    cell. Additionally, saves "depths" of 1's for current row"""

    def maximalRectangle(self, matrix: list[list[str]]) -> int:
        n = len(matrix[0])
        depth = [0] * n
        max_area = 0
        for row in matrix:
            for i in range(n):
                depth[i] = depth[i] + 1 if row[i] == '1' else 0
            rect_dims = []
            for i in range(n):
                if depth[i] == 0:
                    rect_dims = []
                    continue
                height = 0
                for idx, (height, width) in enumerate(rect_dims):
                    if height > depth[i]:
                        break
                    rect_dims[idx] = (height, width + 1)
                    max_area = max(max_area, height * (width + 1))
                if height > depth[i]:
                    rect_dims = rect_dims[:idx]
                    if not rect_dims or rect_dims[-1][0] != depth[i]:
                        rect_dims.append((depth[i], width + 1))
                        max_area = max(max_area, depth[i] * (width + 1))
                elif height < depth[i]:
                    rect_dims.append((depth[i], 1))
                    max_area = max(max_area, depth[i])
        return max_area



print(Solution_Else_1().maximalRectangle([['0', '1', '0', '1', '1', '1', '0', '1'],
                                          ['0', '1', '1', '0', '1', '1', '0', '0'],
                                          ['1', '1', '1', '1', '0', '0', '0', '1'],
                                          ['0', '1', '1', '1', '1', '1', '1', '0'],
                                          ['1', '1', '1', '0', '0', '1', '1', '1']]))

print(Solution2().maximalRectangle([
    ["1","0","1","0","0"],
    ["1","0","1","1","1"],
    ["1","1","1","1","1"],
    ["1","0","0","1","0"]]))

print(Solution2().maximalRectangle([['0', '1', '0', '1', '1', '1', '0']]))
print(Solution2().maximalRectangle([["0","0","0"],["0","0","0"],["1","1","1"]]))
print(Solution2().maximalRectangle([
    ["1","0","1","1","0","1"],
    ["1","1","1","1","1","1"],
    ["0","1","1","0","1","1"],
    ["1","1","1","0","1","0"],
    ["0","1","1","1","1","1"],
    ["1","1","0","1","1","1"]]))