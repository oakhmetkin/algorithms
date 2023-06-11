from huffman_code import HuffmanCode


s = input('Enter str:  ') # e.g. 'aaaabbbbccccde'
print(f'length:     {len(s)}')
print(f'uniq chars: {len(set(s))}')
print()


haffcode = HuffmanCode(s)
print('Tree of characters:')
haffcode.tree.print_tree()
print()
print('Codes dict:', haffcode.encode_dict)
print('Encoded string:', haffcode.get_encoded_str())


# # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#                         EXAMPLE
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
# Enter str:  aaaabbbbccccde
# length:     14
# uniq chars: 5
#
# Tree of characters:
#                 --------b
#         --------█
#                 --------c
# --------█
#                 --------a
#         --------█
#                         --------e
#                 --------█
#                         --------d
#
# Codes dict: {'d': '000', 'e': '001', 'a': '01', 'c': '10', 'b': '11'}
# Encoded string: 010101011111111110101010000001
# # # # # # # # # # # # # # # # # # # # # # # # # # # # #
