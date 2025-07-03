# 🐚 Minishell

> Un shell UNIX minimaliste codé en C. Il gère les commandes, redirections, pipes, variables d’environnement, signaux, builtins… bref, tout ce qu’il faut pour imiter Bash dans ses bases.

---

## 🏷️ Badges

![Norminette](https://img.shields.io/badge/Norminette-OK-success)
![Mandatory](https://img.shields.io/badge/Mandatory-Completed-brightgreen)
![Bonus](https://img.shields.io/badge/Bonus-Done-blue)
![Score](https://img.shields.io/badge/Score-101%2F100-success)

---

## ✅ Statut du Projet

- ✅ **Norminette** : OK  
- ✅ **Partie obligatoire** : OK  
- ✅ **Bonus** : Fait  
- 🏆 **Score final** : 101/100

---

## 🎯 Objectif

Reproduire un shell fonctionnel avec gestion :

- des **commandes** internes et externes  
- des **pipes** et **redirections**
- des **variables d’environnement**
- du **parsing** complexe avec quotes et expansions
- des **signaux** (Ctrl+C, Ctrl+D, Ctrl+\)
- et plus encore…

---

## 🛠️ Installation

```bash
git clone git@github.com:zobzob90/minishell.git
cd minishell
make
./minishell

## Exemple

$ echo Hello World
Hello World

$ export USER=zobzob
$ echo $USER
zobzob

$ ls -l | grep minishell > result.txt

$ cat << EOF
> Ceci est un heredoc
> EOF
Ceci est un heredoc

## Arborescence

minishell/
├── inc/                    # Headers principaux
│   └── minishell.h
├── libft/                  # Libft + printf + get_next_line
│   ├── ft_*.c
│   ├── libft.h
│   ├── ft_printf/
│   └── get_next_line/
├── src/
│   ├── builtin/           # Builtins : cd, echo, export, unset...
│   ├── easter/            # Bonus : prompt personnalisé (michel)
│   ├── env/               # Initialisation et gestion de l'env
│   ├── exec/              # Exécution des commandes
│   ├── expand/            # Expansions des variables ($)
│   ├── lexer/             # Découpage de la ligne en tokens
│   ├── parsing/           # Structure syntaxique
│   ├── signal/            # Gestion des signaux
│   └── utils/             # Fonctions utilitaires
├── main.c                 # Point d'entrée principal
├── Makefile               # Compilation
└── rapport_final.sh       # Script de soumission

📚 Technologies

**Langage C**
Compilation via Makefile
Conforme à la Norme 42

📄 Licence

Projet réalisé dans le cadre du cursus 42 – pas de licence commerciale.

🙋‍♂️ Auteur
👤 zobzob90
🔗 github.com/zobzob90
