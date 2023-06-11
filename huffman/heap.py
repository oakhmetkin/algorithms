class Heap:
    __GAP_STR = '\t'
    __EDGE_STR = '----' * 2

    def __init__(self, t='min', lt=None) -> None:
        '''
        t - type, i.e. min or max
        lt - less than - lambda a, b: a < b
        
        '''
        self.lst = []
        self.is_max_heap = (t == 'max')

        lt = lt if lt else (lambda a, b: a < b)
        self.cmp = lambda a, b: lt(b, a) if self.is_max_heap else lt(a, b)
        

    def get_len(self):
        return len(self.lst)
    
    def pick(self):
        if len(self.lst) > 0:
            return self.lst[0]
        else:
            raise Exception('Heap len = 0')
    
    def extract(self):
        v = self.lst
        if len(v) > 1:
            item = v.pop(0)
            v.insert(0, v.pop())
            self.__heapify_down(0)
            return item
        elif len(v) == 1:
            return v.pop()
        else:
            raise Exception('Heap len = 0')
        
    def insert(self, item):
        v = self.lst
        v.append(item)
        self.__heapify_up(len(v) - 1)

    def __heapify_up(self, ind):
        v = self.lst

        if ind <= 0 or ind >= len(v):
            return
        
        p = (ind - 1) // 2

        if self.cmp(v[ind], v[p]):
            v[p], v[ind] = v[ind], v[p]
            self.__heapify_up(p)

    def __heapify_down(self, ind):
        v = self.lst

        l, r, cur = 2*ind + 1, 2*ind + 2, ind

        if l < len(v) and self.cmp(v[l], v[cur]):
            cur = l
        
        if r < len(v) and self.cmp(v[r], v[cur]):
            cur = r
        
        if cur != ind:
            v[ind], v[cur] = v[cur], v[ind]
            self.__heapify_down(cur)
    
    def print_tree(self, ind=0, gaps=0):
        if ind >= len(self.lst):
            return

        self.print_tree(ind=2*ind + 1, gaps=gaps+1)
        print(f'{Heap.__GAP_STR * gaps}{Heap.__EDGE_STR}{self.lst[ind]}')
        self.print_tree(ind=2*ind + 2, gaps=gaps+1)


if __name__ == '__main__':
    # test
    h = Heap(t='min')

    for n in [3, 2, 3, 7, 8, 5, 4, 3, 5, 6, 4, 6, 7, 8, 1, 9]:
        h.insert(n)

    h.print_tree()
    print('\n\n\n')
    print(h.extract())
    print('\n\n\n')
    h.print_tree()
