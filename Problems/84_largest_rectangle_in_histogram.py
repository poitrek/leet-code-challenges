class Solution:
    def largestRectangleArea(self, heights: list[int]) -> int:
        return max(max(heights[i: j]) * (j - i) for i in range(len(heights)) for j in range(i+1, len(heights)))

