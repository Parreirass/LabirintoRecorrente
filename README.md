# LabirintoRecorrente
AEDS I | CEFET-MG
</div>

<div style="display: inline-block;">
<img align="center" height="20px" width="60px" src="https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white"/> 
<img align="center" height="20px" width="80px" src="https://img.shields.io/badge/Made%20for-VSCode-1f425f.svg"/> 
</a> 
</div>

<p> </p>
<p> </p>

# Problema Proposto

<p align="justify">
	O trabalho <code>Labirinto Recorrente</code> se baseia em um jogo automático e totalmente randômico. Ele consiste, basicamente, em um caminho, composto de matrizes (mapas) quadráticas, que um personagem deve atravessá-las, podendo enfrentar casas com itens (que posteriormente podem lhe gerar vidas), perigos (que tiram-lhe uma vida) ou paredes (que são impossíveis de serem atravessadas). O objetivo do personagem é, através de passos totalmente randômicos, fazer um caminho que passe por todas as matrizes possíveis, caindo em posições com zero itens, sem perder todas as vidas, chegando então à vitória! Caso contrário, o personagem perde todas as vidas e morre, assim, perdendo o jogo!
</p>

# Regras do Jogo
<p align ="justify">
  <div>
    <li>  
      Para ganhar, o personagem deve passar por todas as matrizes e voltar para a matriz inicial sem morrer e fazer todo esse caminho sem adiquirir nenhum item. 
    </li>
    <li>
     Para perder, basicamente, ele deve perder todas as vidas. Ele perde vida passando por perigos (representados pelos <code>*</code> na matriz). Caso ele seja randomizado em uma posição inicial em que existam apenas paredes em volta dele, ele também irá morrer, pois não terá para onde ir.
      </li>
      <li>
       Ao passar por uma casa com itens (casa com um número), o personagem pega um item e o número contido na posição diminui em uma unidade. Caso ele atinja uma casa com número zero, ele não pegará itens nessa posição.
      </li>
      <li>
       Ao atingir 4 itens, o personagem ganha uma vida e zera novamente a contagem de itens.
      </li>
      <li>
       O personagem inicia o jogo com 0 itens e 10 vidas.
      </li>
      <li>
	      O <i><b>teletransporte</i></b> entre as matrizes é feito quando o personagem atinge a última coluna da matriz que ele está posicionado. Caso isso aconteça, seu próximo movimento será na matriz seguinte e sua posição nela será totalmente randômica.
      </li>
      <li>
       O personagem não pode voltar alguma matriz, ou seja, uma vez que ele passou por uma matriz, só retornará nela caso dê uma volta completa por todo o percursso do jogo.
      </li>
      <li>
       A mudança de matriz sempre é em sentido crescente, ou seja, da 1 para a 2, da 2 para a 3, assim sucessivamente.
      </li>
      <li>
       Quando alcançar a última coluna da última matriz, o personagem irá retornar para a matriz de número 1 e iniciará um <i><b>novo ciclo</i></b> no jogo.
      </li>
   </div>
</p>

<p align = "justify">
	Um exemplo de <i><b>ciclo</b></i> de percursso do personagem pode ser visto na imagem abaixo:
</p>

<p align="center">
<img src="img/PossivelCaminho1.jpeg"/> 
</p>

<p align = "justify">
   A partir dessas movimentações do personagem é possível observar que ele conquistou 10 itens no total, ou seja, conseguiu 2 vidas e ainda tem 2 itens em sua <i><b>mochila</b></i>. Entretanto, ele passou por 4 perigos, perdendo assim 4 vidas. Portanto, o personagem terminou seu primeiro <i><b>ciclo</b></i> com 8 vidas e 2 itens na <i><b>mochila</i></b>.
</p>

<p align = "justify">
	No início do seu <i><b>segundo ciclo</b></i>, as matrizes iriam ser inicializadas da seguinte forma:
</p>

<p align="center">
<img src="img/PossivelCaminho2.jpeg"/> 
</p>

<p align = "justify">
  É possível observar que, os caminhos com itens que o personagem passou, tiveram um decréscimo em seus valores de uma unidade, ou seja, cada posição passou a ter um item a menos. 
</p>

<p align="justify">
  É possível observar também que, caminhos que não têm mais itens, tem seu valor setado como <i><b>0</i></b>, ou seja, não são caminhos perigosos, porém também não dão itens ao personagem. Essas posições zeradas ajudam o personagem a ganhar o jogo, já que para ganhar ele deve fazer um percursso todo sem pegar itens.
</p>

<p align="justify">
Uma possível vitória pode ser observada na imagem abaixo:
</p>

<p align="center">
<img src="img/PossivelVitoria.jpeg"/> 
</p>

<p align="justify">
É possível observar que o caminho percorrido pelo personagem em todas as matrizes não o fez conquistar nenhum item. Ele só passou por posições zeradas ou com perigos. Caso ele consiga um caminho como esse e não perca todas as suas vidas, ele ganha o jogo!
</p>
<br>
<br>

# O Algorítmo

<br>
<br>
<p align ="justify">
	O algorítimo foi separado em funções. As três primeiras funções presentes no arquivo .hpp servem para randomizar um número pré estabelecido de matrizes e imprimí-las no arquivo <code>.data</code>. As demais funções servem para o funcionamento do jogo e coordenação do personagem entre as matrizes.
</p>

<p align ="justify">
	Partindo para o funcionamento do jogo, as quatro últimas funções apresentadas no arquivo .hpp são as responsáveis. Inicialmente, a função <code>Ler Matriz</code> faz a leitura das matrizes criadas à partir da randomização, criando o arquivo <code>input.data</code>. Após isso, a função chamada <code>EscreverMatriz</code> separa cada matriz em um arquivo <code>.data</code> separado, para fazer a leitura de cada matriz individualmente, economizando assim, espaço de memória. A função <code>EscreverMatriz</code> também é responsável pelo armazenamento do nome dos arquivos na struct que trabalha com a demarcação das posições já buscadas pelo personagem, chamada <code>CaminhoPercorrido</code>, para fazer a verificação de quantas casas foram exploradas por ele.
</p>

<p align="justify">
	A função responsável pelo funcionamento do jogo, de forma principal, é a chamada <code>PercorrerMatriz</code>. Em primeiro lugar, ela irá verificar em qual matriz o personagem está localizado. Caso ele esteja iniciando o jogo naquele momento ou efetuando seu primeiro passo após um teletransporte, essa função irá randomizar uma posição inicial para o personagem (essa posição não pode ser um perigo e nem uma parede).
</p>

<p align ="justify">
	Caso o personagem já esteja inserido em um novo mapa (matriz), ele irá partir para sua movimentação aleatória. Tal processo se dá em uma randomização de um número de 1 a 8, cada número corresponde à uma possível direção que o personagem irá avançar. 
</p>

<p align ="justify">
	Exemplo: A randomização apresentou o número 3, logo o personagem irá se dirigir ao leste. Caso a posição ao leste tenha um número, o personagem irá ganhar um item!
</p>

<p align ="center">
<img src="img/Terminal1.jpeg">
</p>
<p align ="justify">
	Quando o personagem atingir a última coluna da matriz atual, seu próximo movimento irá ser na matriz seguinte. O terminal irá exibir o novo mapa a ser explorado com a mensagem informado de qual matriz o personagem irá se localizar.
</p>

<p align ="justify">
	Caso a posição randomizada tiver um perigo, o personagem irá perder uma vida!
</p>

<p align ="center">
<img src="img/Terminal2.jpeg">
</p>

<p align ="justify">
	Ao adiquirir 4 itens, o personagem os troca por uma vida!
</p>

<p align ="center">
<img src="img/Terminal3.jpeg">
</p>

<p align="justify">
	Existem duas condições de finalização de jogo, com a derrota ou com a vitória.
</p>

<p align="justify">
	Em caso de derrota, o personagem terá perdido todas as vidas e o terminal irá exibir a mensagem abaixo com as informações da aventura do personagem:  
</p>

<p align ="center">
<img src="img/DerrotaTerminal.jpeg">
</p>

<p align ="justify">
	Já em caso de vitória, o personagme terá que ter feito o caminho proposto nas regras acima. Então, o terminal irá exibir a seguinte mensagem com as informações da batalha que acabara de ser vencida:
</p>

<p align="center">
<img src="img/VitoriaTerminal.jpeg">
</p>

# Conclusão

<p align="justify">
<li>
Quanto ao custo computacional, não é possível fazer uma análise precisa nesse algorítmo. Por ser baseado em uma movimentação totalmente randômica, é possível fazer apenas suposições quanto ao custo computacional. Por exemplo: 
<p>
	</li>
      &emsp; -> Se, em um caso, a movimentação do personagem atingir todas as posições possíveis, o custo do algorítimo é quadrático.
      </p>
      <p>
      &emsp; -> Em outra situação, se sua movimentação for apenas em linha reta, seguindo uma mesma direção até o seu fim, seu custo é próximo do linear.
      </p>
</p>
<p align="justify">
	<li>
O algorítmo apresentado pode ser inferido como uma das melhores formas de execução. O modelo de randomização de movimento apresentado utiliza poucas estruturas de repetição e de condicionamento, podendo, em seu melhor caso, ter seu custo próximo do linear.
</p>
</li>
<li>
	Diante disso, a proposta apresentada foi executada com sucesso através de um algorítmo prático, útil e dinâmico, apresentando resultados condizentes com o esperado.
	</li>

 # Bibliotecas 
<p>É necessário incluir as seguintes bibliotecas para o funcionamento do algorítmo:
<ul>
    <li><code>#include 'iostream'</code></li>
    <li><code>#include 'fstream'</code></li>
    <li><code>#include 'vector'</code></li>
    <li><code>#include 'string'</code></li>
    <li><code>#include 'sstream'</code></li>
    <li><code>#include 'unistd.h'</code></li>
    <li><code>#include 'algorithm'</code></li>
    <li><code>#include 'time.h'</code></li>
    <li><code>#include 'utility'</code></li>
    <li><code>#include 'set'</code></li>
</ul>

# Compilação e Execução

O projeto `Labirinto Recorrente` disponibilizado possui um arquivo Makefile que realiza todo o procedimento de compilação e execução. Para tanto, temos as seguintes diretrizes de execução:


| Comando                |  Função                                                                                           |                     
| -----------------------| ------------------------------------------------------------------------------------------------- |
|  `make clean`          | Apaga a última compilação realizada contida na pasta build                                        |
|  `make`                | Executa a compilação do programa utilizando o gcc, e o resultado vai para a pasta build           |
|  `make run`            | Executa o programa da pasta build após a realização da compilação                                 |

<a style="color:black" href="mailto:felipeparreiras86@gmail.com?subject=[GitHub]%20Source%20Dynamic%20Lists">
✉️ <i>felipeparreiras86@gmail.com</i>
</a>
