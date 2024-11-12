Mapa

Número da Lista: 19<br> Conteúdo da Disciplina: Grafos 1<br>

Alunos
Matrícula	Aluno
21/1061805	Guilherme Westphall de Queiroz
22/1022088	Lucas Martins Gabriel
Sobre
Descreva os objetivos do seu projeto e como ele funciona.

Instalação
Linguagem: C++<br> Framework: wxWidgets<br>

Para rodar o projeto é necessário ter o docker instalado em sua máquina. Para instalar o docker, siga as instruções presentes no site oficial: https://docs.docker.com/get-docker/

Após instalar o docker, execute a sequência de comandos abaixo para rodar o projeto:

Construa a imagem do container (isso pode levar um tempo 😨)
docker build -t cplusplus-wxwidgets-app .
No Linux execute o comando abaixo para garantir que o container tenha acesso a interface gráfica do host
xhost +local:docker
A permissão pode ser removida depois com: xhpst -local:docker

Execute o container
docker run --rm -e DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix cplusplus-wxwidgets-app
No macOS, certifique-se de ter o XQuartz em execução. No Windows, use o Xming para suporte gráfico. Inicie o servidor X e marque a opção "No access control" para permitir conexões de outros hosts. Em seguida, execute o comando abaixo para rodar o container
docker run -e DISPLAY=host.docker.internal:0 cplusplus-wxwidgets-app
