
from graphviz import Digraph




def draw(input_path):
    dot = Digraph(comment='NFA RESULTS')
    with open(input_path, "r") as rf:
        nfa_lines = rf.readlines()

    nodes = set()

    for line in nfa_lines:
        line = line.replace(" ", "").replace("\n", "")
        node1, node2, value = line.split(",")
        nodes.add(node1)
        nodes.add(node2)
        dot.edge(node1, node2, label=value)

    for node in nodes:
        dot.node(node, "{}".format(node))

    dot.format = 'png'
    # dot.view()
    dot.render('{}.gv'.format(input_path), view=True)
    print("[{}] success!!!".format(input_path))

nfa_path = "nfa.txt"
dfa_path = "dfa.txt"
draw(nfa_path)
draw(dfa_path)

