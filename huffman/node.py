class Node:
    __GAP_STR = '\t'
    __EDGE_STR = '----' * 2
    __FILLED_CH = chr(0x2588)

    def __init__(self, count: int, letter: str=None, l=None, r=None) -> None:
        self.count = count
        self.letter = letter
        self.l = l
        self.r = r
    
    def __repr__(self) -> str:
        return f'{self.letter}: {self.count}'
    
    def __str__(self) -> str:
        return f'{self.letter}: {self.count}'
    
    def print_tree(self) -> None:
        Node.__print_tree(self)
    
    @staticmethod
    def __print_tree(node, gaps=0) -> None:
        if not node:
            return
        
        ltr = node.letter if node.letter else Node.__FILLED_CH

        Node.__print_tree(node.r, gaps=gaps+1)
        print(f'{Node.__GAP_STR * gaps}{Node.__EDGE_STR}{ltr}')
        Node.__print_tree(node.l, gaps=gaps+1)
