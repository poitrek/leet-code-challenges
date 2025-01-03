# PASSED

class Solution:
    def restoreIpAddresses(self, s: str) -> list[str]:

        # Dynamic programming solution:

        # sol[k][n] - set of all correct partial IP strings consisting of k octets, including digits 0,1,...,n-1
        # s = 252164350120
        # sol[0][0] = { 2. }  sol[0][1] = { 25. }  sol[0][2] = { 252. }  sol[0][3] = {} (too many digits)
        # sol[1][0] = {} (at least two digits needed)  sol[1][1] = { 2.5. }  sol[1][2] = { 2.52.  25.2. }
        # sol[1][3] = { 25.21.  252.1. } (2.521. incorrect)  sol[1][4] = { 25.216.  252.16. }  sol[1][5] = { 252.164. }
        # sol[2][0] = sol[2][1] = {} (>=3 digits needed)  sol[2][2] = { 2.5.2. }
        # sol[2][3] = { (xx.1 - use sol[k-1][n-1] = sol[1][2]) 2.52.1.  25.2.1. ; (xx.s[n-1]1 = xx.21 - use sol[k-1][n-2] = sol[1][1]) 2.5.21.
        #   (xx.s[n-2]s[n-1]1 = xx.521 -- INCORRECT) }
        # sol[2][4]: s[4] = '6'. 1) xx.s[n] = xx.6 - use sol[k-1][n-1] = sol[1][3]. { 25.21.6. 252.1.6. }.
        # 2) xx.s[n]s[n-1] = xx.16 - use sol[k-1][n-2] = sol[1][2]: { 2.52.16. 25.2.16. }
        # 3) xx.s[n-2]s[n-1]s[n] = xx.216 (216 <= 256, good) - use sol[k-1][n-3] = sol[1][1]: { 2.5.216. }
        # ==> sol[2][4] = { 25.21.6.  252.1.6.  2.52.16.  25.2.16.  2.5.216. }
        # sol[2][5]: s[5] = '4'.  1) xx.s[n] = xx.4 - use sol[k-1][n-1] = sol[1][4]: { 25.216.4.  252.16.4. }
        # 2) xx.s[n]s[n-1] = xx.64 - use sol[k-1][n-2] = sol[1][3]: { 25.21.64.  252.1.64. }
        # 3) xx.s[n-2:n] = xx.164 (ok) - use sol[k-1][n-3] = sol[1][2]: { 2.52.164  25.2.164. }
        # ==> sol[2][5] = { 25.216.4.  252.16.4.  25.21.64.  252.1.64.  2.52.164. 25.2.164. }
        # sol[2][6]: 1) xx.3 --> sol[1][5]: { 252.164.3. } ; 2) xx.43 --> sol[1][4]: { 25.216.43.  252.16.43. }
        # 3) xx.s[n-2:n] = xx.643 -- incorrect: {}. ==> sol[2][6] = { 252.164.3.  25.216.43.  252.16.43. }
        # sol[2][7]: '5'.  1) xx.5 --> sol[1][6]: {} ; 2) xx.35 --> sol[1][5]: { 252.164.35. }
        # 3) xx.435 -- incorrect: {}. ==> sol[2][7] = { 252.164.35. }
        # sol[2][8]: '0'.  1) xx.0 -- incorrect (0) ; 2) xx.50 -> sol[1][6]: {} ; 3) xx.350 -- incorrect: {}.
        # ==> sol[2][8] = {}
        # sol[2][9] = {} (10 digits, 3 octets)
        # k = 3
        # sol[3][0]=sol[3][1]=sol[3][2] = {}
        # sol[3][3] = { 2.5.2.1 }
        # sol[3][4]: xx.6 -> sol[2][3]: { 2.52.1.6.  25.2.1.6.  2.5.21.6. } 2) xx.16 -> sol[2][2]:
        # { 2.5.2.16. } ; 3) xx.216 -> sol[2][1]: {}. ==> sol[3][4] = { 2.52.1.6.  25.2.1.6.  2.5.21.6.  2.5.2.16. }

        if len(s) < 4 or len(s) > 12:
            return []
        sol = [[set() for _ in range(len(s) + 1)] for __ in range(4 + 1)]
        # k = 0 - consists of 0 octets; n = 0 - includes no digits from s (empty string '')
        sol[0][0] = {''}
        for k in range(1, 4 + 1):
            for n in range(1, len(s) + 1):
                # Only s[n-1] for octet
                for ip_part in sol[k-1][n-1]:
                    sol[k][n].add(ip_part + '.' + s[n-1])
                # s[n-2]s[n-1] for octet
                if n >= 2 and s[n-2] != '0':
                    for ip_part in sol[k-1][n-2]:
                        sol[k][n].add(ip_part + '.' + s[n-2: n])
                # s[n-3]s[n-2]s[n-1] for octet
                if n >= 3 and s[n-3] != '0' and int(s[n-3: n]) <= 255:
                    for ip_part in sol[k-1][n-3]:
                        sol[k][n].add(ip_part + '.' + s[n-3: n])
                # print(f'sol[{k}][{n}] = f{sol[k][n]}')

        return [result[1:] for result in sol[4][len(s)]]


print(Solution().restoreIpAddresses('1112110101'))
print(Solution().restoreIpAddresses('111111111'))
