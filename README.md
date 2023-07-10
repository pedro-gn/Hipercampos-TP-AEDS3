# Hipercampos-TP-AEDS3
Trabalho da disciplina AEDS3.


O trabalho consiste na criação de um código para a solução do seguinte problema: dadas duas âncoras A=(Xa, 0) e B=(Xb, 0) formando um segmento horizontal, e um conjunto P de N de pontos (X, Y), tal que X > 0 e Y > 0, é preciso que o código calcule a quantidade máxima de pontos que possam ser “ligados” as âncoras A e B de modo que as ligações formadas pelos segmentos de reta se interceptam apenas nas âncoras. Uma “ligação” de um ponto u ∈ P é dada pelos segmentos de reta (u, A) e (u, B).

Na imagem a seguir a figura a esquerda representa uma possível entrada, a do meio representa uma ligação inválida pois os segmentos formados pela “ligação” dos pontos 1 e 4 se interceptam, já a última figura mostra uma possível solução válida em que os segmentos se interceptam apenas na âncora.

![](https://lh3.googleusercontent.com/Q-0qyX3VA6K746YoSe6yW1l6ODQ4W6K39P4WLOVYJyH5hNwi-Vw_zkEZgNPVKkd928pIYt7L95TBr7UWHX86Sk9-mGwymD09JGeaiTZ2Ju8ixJEg-_nU7xDwyfkOcSfp8xtbVi66A4COfY3wOBZL3VU)

(Imagem retirada da especificação do trabalho)


**Depois da compilação do código com o make, será gerado um executável com o nome “tp1”, ele recebe dois parâmetros na linha de comando, o arquivo de entrada (-i ) e o arquivo de saída ( -o ). Um exemplo seria: ./tp1 -i “nomeEntrada” -o“nomeSaida” .**
