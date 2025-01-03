class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        s = list(s)
        buffer = []
        max_length = 0
        for c in s:
            if c in buffer:
                max_length = max(max_length, len(buffer))
                idx = buffer.index(c)
                buffer = buffer[idx+1:]
            buffer.append(c)
        return max(max_length, len(buffer))


print(Solution().lengthOfLongestSubstring('a'))
print(Solution().lengthOfLongestSubstring('abcde'))
print(Solution().lengthOfLongestSubstring('abcade'))
print(Solution().lengthOfLongestSubstring('abcadae'))
