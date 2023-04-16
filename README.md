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

<p align="justify">
	O trabalho "Labirinto Recorrente" se baseia em um jogo automático e totalmente randômico. Ele consiste, basicamente, em um caminho, composto de matrizes (mapas) quadráticas, que um personagem deve atravessá-las, podendo enfrentar casas com itens (que posteriormente podem lhe gerar vidas), perigos (que tiram-lhe uma vida) ou paredes (que são impossíveis de serem atravessadas). O objetivo do personagem é, através de passos totalmente randômicos, fazer um caminho que passe por todas as matrizes possíveis, caindo em posições com zero itens, sem perder todas as vidas, chegando então à vitória! Caso contrário, o personagem perde todas as vidas e morre, assim, perdendo o jogo!
</p>

<p align ="justify">
	O algorítimo foi separado em funções. As três primeiras funções presentes no arquivo .hpp servem para randomizar um número pré estabelecido de matrizes e imprimí-las no arquivo .data. As demais funções servem para o funcionamento do jogo e coordenação do personagem entre as matrizes.
</p>

<p align ="justify">
	Como qualquer jogo, ele também possui algumas regras:
  <div>
    <p>  
      &emsp; - Para ganhar, o personagem deve passar por todas as matrizes e voltar para a matriz inicial sem morrer e fazer todo esse caminho sem adiquirir nenhum item. 
    </p>
    <p>
      &emsp; - Para perder, basicamente, ele deve perder todas as vidas. Ele perde vida passando por perigos (representados pelos "*" pela matriz). Caso ele seja randomizado em uma posição inicial em que existam apenas paredes em volta dele, ele também irá morrer, pois não terá para onde ir.
      </p>
      <p>
      &emsp; - Ao passar por uma casa com itens (casa com um número), o personagem pega um item e o número contido na posição diminui em uma unidade. Caso ele atinja uma casa com número zero, ele não pegará itens nessa posição.
      </p>
      <p>
      &emsp; - Ao atingir 4 itens, o personagem ganha uma vida e zera novamente a contagem de itens.
      </p>
      <p>
      &emsp; - O personagem inicia o jogo com 0 itens e 10 vidas.
      </p>
      <p>
      &emsp; - O "teletransporte" entre as matrizes é feito quando o personagem atinge a última coluna da matriz que ele está posicionado. Caso isso aconteça, seu próximo movimento será na matriz seguinte e sua posição nela será totalmente randômica.
      </p>
      <p>
      &emsp; - O personagem não pode voltar alguma matriz, ou seja, uma vez que ele passou por uma matriz, só retornará nela caso dê uma volta completa por todo o percursso do jogo.
      </p>
      <p>
      &emsp; - A mudança de matriz sempre é em sentido crescente, ou seja, da 1 para a 2, da 2 para a 3, assim sucessivamente.
      </p>
      <p>
      &emsp; - Quando alcançar a última coluna da última matriz, o personagem irá retornar para a matriz de número 1 e iniciará um "novo ciclo" no jogo.
      </p>
   </div>
</p>

<p align = "justify">
  Um exemplo de "ciclo" de percursso do personagem pode ser visto na imagem abaixo:
</p>

<p align="center">
<img src="img/PossivelCaminho1.jpeg"/> 
</p>

<p align = "center">
   A partir dessas movimentações do personagem é possível observar que ele conquistou 10 itens no total, ou seja, conseguiu 2 vidas e ainda tem 2 itens em sua "mochila". Entretanto, ele passou por 4 perigos, perdendo assim 4 vidas. Portanto, o personagem terminou seu primeiro "ciclo" com 8 vidas e 2 itens na "mochila".
</p>

<p align = "center">
   No início do seu "segundo ciclo", as matrizes iriam ser inicializadas da seguinte forma:
</p>

<p align="center">
<img src="images/matriz_gulosa_editada.png"/> 
</p>
