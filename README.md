# Campo Minado (Terminal C)

Implementação de um Minesweeper que roda no terminal, escrita em C, com interface colorida por ANSI, emojis e animações simples. Permite definir dimensões do tabuleiro, quantidade de minas, usar bandeiras e pedir dicas. Funciona em Linux/macOS (terminal com suporte ANSI) e no Windows 10+ (Console UTF-8).


## Demonstração

![Mine](https://github.com/user-attachments/assets/d056ffa8-c19f-4b86-b8c3-e83c34327f05)


## Sumário
- [Sobre o projeto](#sobre-o-projeto)
- [Funcionalidades principais](#funcionalidades-principais)
- [Controles do jogo (entrada no terminal)](#controles-do-jogo-entrada-no-terminal)
- [Como jogar (fluxo)](#como-jogar-fluxo)
- [Dicas de jogo](#dicas-de-jogo)
- [Como compilar e executar](#como-compilar-e-executar)
- [Estrutura do projeto](#estrutura-do-projeto)
- [Compatibilidade e observações](#compatibilidade-e-observações)
- [Créditos](#créditos)


## Sobre o projeto
Este projeto implementa o clássico Campo Minado totalmente em terminal:
- Interface em texto com cores e bordas, usando sequências ANSI.
- Emojis para quadrados, bandeiras e explosões.
- Lógica de primeira jogada garantida: a primeira abertura nunca acerta uma bomba (realocação automática).
- Sistema de dicas para ajudar quando travar.

O foco é didático e divertido, com um código modular separando interface (desenho/menus), regras do jogo e estrutura do tabuleiro.


## Funcionalidades principais
- Dimensões personalizadas do tabuleiro:
  - Linhas: 5 a 26 (rotuladas de A a Z)
  - Colunas: 5 a 40 (numéricas)
- Quantidade de minas configurável:
  - Mínimo: 7
  - Máximo: floor(largura × altura / 5), mostrado na interface
- Primeira jogada segura: realoca a bomba caso a primeira célula aberta tenha mina.
- Bandeiras: marcar e desmarcar posições suspeitas.
- Dica: pressione apenas Enter para receber uma sugestão de jogada segura quando possível.
- Interface colorida com bordas, cabeçalho de comandos e animações simples de explosão.
- Detecção de vitória e exibição de todas as bombas ao finalizar a partida.
- Entradas validadas com mensagens de erro amigáveis.


## Controles do jogo (entrada no terminal)
- Abrir célula: [Letra][Número]
  - Ex.: A1, C10, F7
- Colocar bandeira: #[Letra][Número]
  - Ex.: #B3
- Remover bandeira: ![Letra][Número]
  - Ex.: !B3
- Dica: pressione Enter (linha vazia)

![Captura de tela 2025-04-25 103147](https://github.com/user-attachments/assets/4dedd519-36c3-401c-b501-e849c692b99d)

Observações:
- Letras podem ser minúsculas ou maiúsculas (a1 equivale a A1).
- Coordenadas válidas dependem do tamanho escolhido.


## Como jogar (fluxo)
1. Início: digite 1 para começar.
2. Informe as dimensões no formato Linha x Coluna (ex.: 10x15). Limites: 5–26 (linhas) e 5–40 (colunas).
3. Informe a quantidade de minas (entre 7 e o máximo sugerido para o tamanho).
4. O tabuleiro será desenhado. Use os comandos acima para jogar.
5. A primeira jogada nunca é bomba. Se abrir uma mina depois disso, a partida termina e o tabuleiro é revelado.
6. Vença ao revelar todos os campos seguros.


## Dicas de jogo
- Comece abrindo posições centrais para revelar mais área.
- Use os números: se uma célula indica 3 e há exatamente 3 vizinhos ocultos, todos são bombas; marque-os com bandeira.
- Após marcar bandeiras, abra células vizinhas que estejam seguras.
- Pressione Enter para receber uma dica quando travar (o sistema tenta sugerir uma posição não-bomba com base nas informações disponíveis).
- Em tabuleiros grandes, recomenda-se deixar o terminal em tela cheia para melhor visualização.


## Como compilar e executar
```bash
# Linux/macOS
make
./campominado

# ou, sem Make
gcc main.c src/interface/interface.c src/jogo/jogo.c src/jogo/tabuleiro.c -Isrc -lm -o campominado
./campominado

# Windows (MinGW/MSYS2)
make
campominado.exe

# ou, sem Make
gcc main.c src/interface/interface.c src/jogo/jogo.c src/jogo/tabuleiro.c -Isrc -lm -o campominado
campominado.exe

# Limpar artefatos de build
make clean
```


## Estrutura do projeto
```
.
├─ Makefile                 # Build (alvos: campominado, clean)
├─ README.md                # Documentação do projeto
├─ main.c                   # Ponto de entrada: inicia menus e fluxo do jogo
├─ src/
│  ├─ interface/
│  │  ├─ interface.c        # UI: desenho do tabuleiro, menus, animações, UTF-8/cores
│  │  └─ interface.h
│  └─ jogo/
│     ├─ jogo.c             # Núcleo do jogo: comandos, dicas, estado e fim de jogo
│     ├─ jogo.h
│     ├─ tabuleiro.c        # Estruturas do tabuleiro, bombas, revelar recursivo, bandeiras, vitória
│     └─ tabuleiro.h
├─ .vscode/                 # Configurações do VS Code (opcional)
├─ .qodo/                   # Metadados do assistente (ignorar)
└─ .git/                    # Metadados do Git
```


## Compatibilidade e observações
- ANSI/cores: requer terminal com suporte a ANSI (padrão em Linux/macOS e Windows 10+). Em Windows antigos, as cores podem não aparecer como esperado.
- UTF-8/emojis: o jogo usa emojis (🔲 🚩 💣 💥). Em alguns terminais/fontes, os símbolos podem não aparecer ou quebrar o espaçamento. Se necessário, troque a fonte do terminal ou reduza a janela.
- Windows: o código ajusta o console para UTF-8 automaticamente. Se estiver usando MinGW/MSYS2, execute no terminal fornecido por eles (MSYS2/MinGW64) para melhor suporte.


## Créditos
- Lucas Magalhães Fontenele Bizeril — Organização, Interface, Makefile, Algumas funções do Tabuleiro, ajustes e validações.
- Marcos Vinicius Pereira Araujo — Estrutura de dados e funções de tabuleiro e jogo.
- Felipe Gabriel Lima Florindo — Makefile e funções em Jogo/Tabuleiro/Interface.

