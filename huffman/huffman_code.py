from heap import Heap
from node import Node


class HuffmanCode:
    def __init__(self, s: str) -> None:
        if len(s) == 0:
            raise ValueError('Length of s must be more than zero!')

        self.s = s
        self.__enc_str = None

        self.tree = HuffmanCode.get_tree(s)
        self.encode_dict = HuffmanCode.get_codes_by_tree(self.tree)
        
        swap = lambda p: (p[1], p[0])
        self.decode_dict = dict(map(swap, self.encode_dict.items()))

    def get_encoded_str(self) -> str:
        if self.__enc_str:
            return self.__enc_str
        
        self.__enc_str = ''

        for c in self.s:
            self.__enc_str += self.encode_dict[c]
        
        return self.__enc_str

    @staticmethod
    def get_tree(s: str) -> Node:
        letters = {}

        for c in s:
            if c in letters:
                letters[c] += 1
            else:
                letters[c] = 1
        
        nodes = [Node(l[1], letter=l[0]) for l in letters.items()]
        assert len(nodes) >= 1, 'no symbols!'

        heap = Heap(t='min', lt=lambda a, b: a.count < b.count)

        for n in nodes:
            heap.insert(n)

        while heap.get_len() > 1:
            f, s = heap.extract(), heap.extract()
            n = Node(count=(f.count + s.count), l=f, r=s)
            heap.insert(n)

        return heap.extract()

    @staticmethod
    def get_codes_by_tree(node: Node, prefix='', letter_code=None) -> dict:
        if not letter_code:
            letter_code = {}
        
        if node.letter:
            letter_code[node.letter] = prefix
        else:
            letter_code = HuffmanCode.get_codes_by_tree(
                    node.l, 
                    prefix=prefix+'0', 
                    letter_code=letter_code
                )
            letter_code = HuffmanCode.get_codes_by_tree(
                    node.r, 
                    prefix=prefix+'1',
                    letter_code=letter_code
                )

        return letter_code
