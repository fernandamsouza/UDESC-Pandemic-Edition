# Arquivo para gerar o grafo normal e dfs, bem como suas ligações

from graphviz import Graph

dot = Graph(comment='TEG')
dotfs = Graph(comment='DFS')

dfs = open('arquivo.txt')
entrada = open('out.txt')

def grafoNormal():
    vizinhos = []

    for linha in entrada:
        dot.node(str(linha[0]))
        linha = linha.split(" ")
        aux = linha[1:-1]
        vizinhos.insert(int(linha[0]), aux)
        for palavra in aux:
            if(not(str(palavra) in dot.body)):
                dot.node(str(palavra))
            if( (len(vizinhos) > int(palavra))):
                if(not(linha[0] in vizinhos[int(palavra)])):
                    dot.edge(str(linha[0]),str(palavra))
            else:
                dot.edge(str(linha[0]),str(palavra))

def grafoDfs():
    aux = dfs.readline()
    dotfs.node(aux)
    for linha in dfs.readlines()[0:]:
        linhaList = linha.replace("\n","")
        linhaList = linhaList.split(" ")
        print(linhaList)
        if(len(linhaList)>=2):
            dotfs.node(linhaList[-1])
            dotfs.edge(linhaList[-1],linhaList[-2])
        else:
            dotfs.node(linhaList[0])
            dotfs.edge(linhaList[0],aux)
            aux = linhaList[0]
# FOII
grafoNormal()
grafoDfs()
entrada.close()
dot.render('imagem.gv', view = True, format = 'pdf', )
dotfs.render('dfs.gv', view = True, format = 'pdf', )