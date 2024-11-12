Fluxo de Engenharia de Software

**Número da Lista**: 19<br>
**Conteúdo da Disciplina**: Grafos 1<br>

## Alunos
| Matrícula  | Aluno                          |
| ---------- | ------------------------------ |
| 21/1061805 | Guilherme Westphall de Queiroz |
| 22/1022088 | Lucas Martins Gabriel          |

## Sobre 
O objetivo do projeto é solucionar exercícios de juiz virutal sobre os algoritmos trabalhados no módulo de grafos 1.
Obs: Tentamos criar gráfica e aplciar uma ordenação topológica no fluxograma de Engenharia de Software da FGA, porém devido a alguns contratempos iremos entregar apenas os exercícios feitos em plataformas virtuais. 

## Instalação 

**Linguagem**: C++<br>
**Framework**: wxWidgets<br>

Para rodar o projeto é necessário ter o docker instalado em sua máquina. Para instalar o docker, siga as instruções presentes no site oficial: https://docs.docker.com/get-docker/
Após instalar o docker, execute a sequência de comandos abaixo para rodar o projeto:
1. Construa a imagem do container (isso pode levar um tempo 😨)
```bash
docker build -t cplusplus-wxwidgets-app .
```
2. No Linux execute o comando abaixo para garantir que o container tenha acesso a interface gráfica do host
```bash
xhost +local:docker
```
> A permissão pode ser removida depois com: `xhpst -local:docker`
3. Execute o container
```bash
docker run --rm -e DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix cplusplus-wxwidgets-app
```

4. No macOS, certifique-se de ter o **XQuartz** em execução. No Windows, use o **Xming** para suporte gráfico. Inicie o servidor X e marque a opção "No access control" para permitir conexões de outros hosts. Em seguida, execute o comando abaixo para rodar o container
```bash
docker run -e DISPLAY=host.docker.internal:0 cplusplus-wxwidgets-app
```