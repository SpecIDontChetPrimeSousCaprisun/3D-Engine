# 3D-Engine
### Francais
(Je m'éscuse en avance pour mon orthographe désastreuse)
Ce projet a été fait en 2026 pour l'école de la transition pendant la periode sur le thème du japon.
Malgrés le manque de rapport entre le thème et le projet j'ai quand mème eu le droit de le faire.

### English
This project was made in 2026 for l'Ecole De La Transition (a french college) durong a period on the theme of japan. 
I was able to make this project even with the lack of coherence between the theme and the project.

## Controlles / Controls
### Francais
Z = avancer tout droit
S = reculer
Q = aller a guauche
D = aller a droite
Alt = vérouiller / déverouiller la souris

La caméra est bougée par la souris

### English
Z = forwards
S = backwards
Q = go left
D = go right
Alt = Lock / unlock mouse

The camera is controlled by the mouse

## Pour les gens voulant utiliser le projet pour apprendre / For people who want to use this project to learn
### Francais
JE NE RECOMMANDE ABSOLUMENT PAS D'UTILISER CE PROJET POUR APPRENDRE A CODER EN C++.
Vous pouvez parcontre l'utilizer pour apprendre les mathématiques autour de la 3D.

<details>
<summary>Comment passer de la 3D à la 2D (comment afficher des points 3d sur l'écran)</summary>
En 3D il y a 3 coordonées : x, y, z
  
x étant l'horizontale,
y étant la hauteur,
et z étant la profondeur

A noter : en fonction de la rotation cette perspéctive peut changer

En 2d (et donc sur l'écran) il y à 2 coordonées : x, y

x étant l'horizontale
et y étant la verticale

A noter : contrairement a la 3d cela ne change jamais

Pour passer de la 3d à la 2d on divise x et y par z

x' = x / z

y' = y / z

(ici x' et y' sonts les coordonées en 2d)

Ceci est utilisé dans la fonction getScreenCoordinates() a l'interieure de Line.cpp :
'''c++
float px1 = (newStart.x / newStart.z) * focalLength;
float py1 = (newStart.y / newStart.z) * focalLength;

float px2 = (newEnd.x / newEnd.z) * focalLength;
float py2 = (newEnd.y / newEnd.z) * focalLength;
'''
</details>

## Pour les gens venant de l'école
Ce projet est donc le projet d'informatique de la periode. Les autres projets étant : 
- Projet d'art
- Projet de cuisine
- Projet de décoration (je suis pas éxactement sûr du nom)

Si vous avez votre propre model 3D que vous voulez voir dans l'éxécutable vous pouvez l'utiliser comme cela :
### Windows
- Ouvrez votre cmd
- entrez : <le chemin de l'éxécutable> <le chemin du fichier 3D>

### Linux
Même chose mais dans un terminal bash classique

Les formats supportés (à ma connaissance) sonts : .obj, .fbx
