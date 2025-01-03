class Solution(object):

    def boardToSequence(self, board):
        sequence = []
        is_odd = True
        for row in board[::-1]:
            if is_odd:
                sequence.extend(row)
            else:
                sequence.extend(row[::-1])
            is_odd = 1 - is_odd
        return sequence

    def snakesAndLaddersSequence(self, sequence):
        if len(sequence) == 1:
            return 0
        final_node = len(sequence) - 1
        to_visit = [0]
        seen_nodes = set()
        n_moves = 0
        while to_visit:
            to_visit_next = []
            for node in to_visit:
                if node == final_node:
                    return n_moves
                max_empty_node = -1
                for next_node in range(node+1, min(node+6, final_node) + 1):
                    if sequence[next_node] == -1:
                        max_empty_node = next_node
                        # seen_nodes.add(next_node)
                    else:
                        target_node = sequence[next_node]
                        if target_node not in seen_nodes:
                            to_visit_next.append(target_node)
                            seen_nodes.add(target_node)
                if max_empty_node != -1 and max_empty_node not in seen_nodes:
                    to_visit_next.append(max_empty_node)
                    seen_nodes.add(max_empty_node)
            to_visit = to_visit_next
            n_moves += 1
        return -1

    def snakesAndLadders(self, board):
        """
        :type board: List[List[int]]
        :rtype: int
        """
        sequence = self.boardToSequence(board)
        sequence = [x - 1 if x != -1 else x for x in sequence]
        return self.snakesAndLaddersSequence(sequence)


if __name__ == '__main__':
    b1 = [
        [16, 15, 14, 13],
        [9, 10, -1, 12],
        [8, -1, 6, 5],
        [1, 2, 3, 4]
    ]
    b2 = [[-1, -1, -1, -1, -1, -1], [-1, -1, -1, -1, -1, -1], [-1, -1, -1, -1, -1, -1], [-1, 35, -1, -1, 13, -1],
     [-1, -1, -1, -1, -1, -1], [-1, 15, -1, -1, -1, -1]]
    print(Solution().snakesAndLadders(b2))
    # print(Solution().boardToSequence([[-1,1,1,1],[-1,7,1,1],[16,1,1,1],[-1,1,9,1]]))
