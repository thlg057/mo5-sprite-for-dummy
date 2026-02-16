# Projet MO5 – Création et affichage de sprites en C

## 🧭 Objet du projet

Ce projet a pour but de montrer **comment créer des sprites en C pour le Thomson MO5** et comment les utiliser dans un programme :

- Création d’un sprite respectant les contraintes graphiques du MO5
- Conversion d’une image en structures C exploitables
- Affichage du sprite à l’écran
- Déplacement du sprite

L’objectif est de fournir une base simple pour démarrer le développement graphique sur MO5.

---

## ⚙️ Prérequis

### 📦 Dans Codespaces

Installer les dépendances nécessaires :

```bash
sudo apt update
sudo apt install flex
pip install Pillow
```

---

### 🐧 Sur machine Linux / Raspberry Pi

Installer les outils de compilation et dépendances :

```bash
sudo apt update
sudo apt install build-essential flex bison libboost-all-dev libxml2-dev zlib1g-dev wget tar
sudo apt install python3 python3-pip python3-venv python3-pil
```

---

## 🛠️ Installation des outils

### Installation de lwtools

Téléchargement :

```bash
wget http://www.lwtools.ca/releases/lwtools/lwtools-4.24.tar.gz
```

Extraction :

```bash
tar -xzf lwtools-4.24.tar.gz
cd lwtools-4.24
```

Compilation et installation :

```bash
make
sudo make install
```

---

### Installation de CMOC

Téléchargement (prendre la dernière version disponible) :  
http://gvlsywt.cluster051.hosting.ovh.net/dev/cmoc.html#download

Téléchargement :

```bash
wget http://gvlsywt.cluster051.hosting.ovh.net/dev/cmoc-0.1.97.tar.gz
```

Extraction :

```bash
tar -xzf cmoc-0.1.97.tar.gz
cd cmoc-0.1.97
```

Configuration, compilation et installation :

```bash
./configure
make
sudo make install
```

---

## 🧰 Installation de l’environnement MO5

Avant de compiler pour la première fois, lancer :

```bash
make install
```

Cette commande :

- Télécharge et utilise le projet **BootFloppyDisk** pour générer les images disquettes bootables  
  👉 https://github.com/OlivierP-To8/BootFloppyDisk.git

- Compile le **sdk_mo5**, basé sur le code helper facilitant le développement sur Thomson MO5  
  👉 https://github.com/thlg057/sdk_mo5.git

- Exporte tous les fichiers nécessaires dans le dossier :

```
tools/
```

Une fois terminé, l’environnement est prêt ✅

---

## 🎨 Création et conversion d’un sprite

Un sprite **32×32 pixels** est fourni dans :

```
/assets
```

Ce sprite a été dessiné en respectant les contraintes du MO5 :

- 2 couleurs maximum pour 8 pixels
- 1 octet pour la forme  
  - 0 = couleur de fond  
  - 1 = couleur de forme
- 1 octet pour la couleur  
  - 4 bits fond  
  - 4 bits forme

---

### Conversion en structure C

Pour convertir l’image PNG en fichier exploitable en C :

```bash
make convert IMG=./assets/[nom_du_sprite].png
```

Cela génère :

```
/include/assets/[nom_du_sprite].h
```

---

### Contenu du fichier généré

Dans ce `.h`, on trouve :

- La définition binaire de la **forme**
- La définition des **couleurs**
- Un exemple d’appel de fonction pour afficher le sprite

Exemple fourni : `perso.h`

---

## 🧪 Compilation du projet

Une fois le sprite converti, il suffit de compiler :

```bash
make
```

Cela :

- Compile le programme C
- Génère l’image disquette
- Permet de lancer le projet sur émulateur ou matériel réel

---

## 🚀 Développement

Après ces étapes, tout est prêt pour :

- Créer de nouveaux sprites
- Les convertir
- Les afficher
- Gérer leurs déplacements

Bon dev sur MO5 ✨
