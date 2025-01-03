### SOLVED ###

from itertools import permutations
from time import sleep
from timer import Timer


def string_permutations(s: str):
    return set(map(lambda x: "".join(x), permutations(s)))

def gen_scrambles(s: str) -> set[str]:
    if not s:
        raise ValueError("s cannot be empty!")
    if len(s) == 1:
        return {s}
    scrambles = set()
    for pos in range(1, len(s)):
        x = s[:pos]
        y = s[pos:]
        # print(f"{x}-{y}")
        x_scrambles = gen_scrambles(x)
        y_scrambles = gen_scrambles(y)
        for x_sc in x_scrambles:
            for y_sc in y_scrambles:
                scrambles.add(x_sc + y_sc)
                scrambles.add(y_sc + x_sc)
    return scrambles


class Solution:

    def __init__(self):
        self.scramble_dict = dict()
        self.n_repeated_recursions = 0

    def isScramble(self, s1: str, s2: str) -> bool:
        if not self.is_permutation(s1, s2):
            return False
        result = self.is_scramble_rec(s1, s2)
        print(f"scramble dictionary: {self.scramble_dict}")
        print(f"{len(self.scramble_dict)} elements")
        print(f"{self.n_repeated_recursions} repeated recursions")
        return result

    def is_permutation(self, s1, s2) -> bool:
        return sorted(s1) == sorted(s2)

    def is_scramble_rec(self, s1, s2) -> bool:
        # sleep(0.3)
        # indent = '-' * rec_depth + ' '
        # print(f"{indent}comparing: ({s1}, {s2})")
        if len(s1) <= 3 or s1 == s2:
            return True
        if (s1, s2) in self.scramble_dict:
            self.n_repeated_recursions += 1
            return self.scramble_dict[(s1, s2)]
        N = len(s1)
        # for pos in range(1, N // 2 + 1):
        for pos in range(1, N):
            x1 = s1[:pos]
            x2 = s2[:pos]
            if self.is_permutation(x1, x2):
                x1_rest = s1[pos:]
                x2_rest = s2[pos:]
                # sleep(0.3)
                # print(f"{indent}pos={pos} [{x1}]{x1_rest}, [{x2}]{x2_rest}")
                if self.is_scramble_rec(x1, x2) and self.is_scramble_rec(x1_rest, x2_rest):
                    self.scramble_dict[(s1, s2)] = True
                    return True
            x2_back = s2[N - pos:]
            if self.is_permutation(x1, x2_back):
                x1_rest = s1[pos:]
                x2_back_rest = s2[: N - pos]
                # sleep(0.3)
                # print(f"{indent}pos={pos} [{x1}]{x1_rest}, {x2_back_rest}[{x2}]")
                if self.is_scramble_rec(x1, x2_back) and self.is_scramble_rec(x1_rest, x2_back_rest):
                    self.scramble_dict[(s1, s2)] = True
                    return True
            # print(s1[:pos], '-', s2[:pos])
            # print(s1[:pos], '-', s2[N-pos:])
            # for pos in range(N // 2 + 1, N):
            #     print(s1[pos:], '-', s2[pos:])
            #     print(s1[pos:], '-', s2[:N-pos])

        self.scramble_dict[(s1, s2)] = False
        return False


def is_scramble(s1, s2):
    return Solution().isScramble(s1, s2)


def test_is_scramble():
    assert is_scramble('1', '1')
    assert is_scramble('12', '12')
    assert is_scramble('12', '21')
    assert is_scramble('312', '123')
    assert is_scramble('12345', '12345')
    assert is_scramble('12345678', '56312478')
    assert is_scramble('12345678', '62145378')

    assert is_scramble('11', '11')
    assert is_scramble('112', '121')
    assert is_scramble('112233', '332211')
    assert is_scramble('1234563', '3534621')
    assert is_scramble('1234563', '6342513')


    def test_with_gen(s: str):
        scrs = gen_scrambles(s)
        for scr in scrs:
            assert is_scramble(s, scr), f"incorrect answer for: s={s}, scr={scr}"
        for not_scr in string_permutations(s) - scrs:
            assert not is_scramble(s, not_scr)
    test_with_gen('1534563')

    s = '12345678'
    Timer.start_measure()
    test_with_gen(s)
    print(f"test_with_gen({s}) completed in {Timer.get_time():.4f} s")

    print("TEST SUCCESS")


# print(is_scramble('12345678', '56312478'))
# test_is_scramble()
# print(is_scramble('aacbcbcadaaedceaaacad', 'adcaacabaddaceacbceaa'))
# print(is_scramble('eebaacbcbcadaaedceaaacad', 'eadcaacabaddaceacbceaabe'))
# print(is_scramble('eebaacbcbcadaaedceaaacadccd', 'eadcaacabaddaceacbceaabeccd'))
print(is_scramble('aabeaaabdcedbeccaaacebcecdaaaaaeebaacbcbcadaaedceaaacadccd', 'eadcaacabaddaceacbceaabeccdaabeaaabdcedbeccaaacebcecdaaaaa'))

# input = '12345678'
# scr = gen_scrambles(input)
# print(f"scrambles {len(scr)}: {scr}")
# perms = string_permutations(input)
# print(f"perms {len(perms)}: {perms}")
# others = perms-scr
# print(f"Other {len(others)}: {others}")
#
# print(f"perms {len(perms)}")
# print(f"scrambles {len(scr)}")
# print(f"others {len(others)}")


