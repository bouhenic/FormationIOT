# Tableau de Bord Météo avec Node-RED

Ce projet consiste à créer un tableau de bord interactif affichant la date, l'heure et les informations météorologiques pour la ville de Clichy en utilisant Node-RED.

## 🎯 Objectifs

- Créer une interface de tableau de bord moderne
- Afficher l'heure et la date en temps réel
- Intégrer les données météorologiques d'OpenWeatherMap
- Visualiser les informations météo (température, humidité, pression)
- Afficher les heures de lever et coucher du soleil

## 📋 Prérequis

- Node-RED installé
- Les nodes suivants installés :
  - node-red-dashboard
  - node-red-contrib-moment
  - node-red-node-openweathermap

## 🚀 Installation des Nodes Requis

1. Ouvrir le gestionnaire de palette dans Node-RED (Menu hamburger > Manage palette)
2. Dans l'onglet "Install", rechercher et installer :
   - `node-red-dashboard`
   - `node-red-contrib-moment`
   - `node-red-node-openweathermap`
3. Actualiser la page du navigateur après l'installation

## 📝 Instructions de Configuration

### 1. Configuration de l'Horloge

1. Créer un nouveau flow
2. Configurer l'affichage sans barre de titre
3. Appliquer les styles suivants :
   - Date : taille de 2em
   - Heure : taille de 7em
   - Couleur : jaune

### 2. Configuration de la Météo

1. Créer un compte OpenWeatherMap :
   - Suivre les instructions sur [OpenWeatherMap](https://openweathermap.org)
   - Obtenir une clé API
   - Note : En cas de délai pour l'obtention de la clé, utiliser : `ebf8764652e8aa99e8f3f355eb84e6a6`

2. Configurer le node OpenWeatherMap :
   - Insérer la clé API
   - Ville : Clichy
   - Pays : France

3. Extraire les données météo :
   - Température
   - Humidité
   - Pression
   - Localisation
   - Détails météo

4. Visualisation :
   - Utiliser des nodes Gauge pour afficher les métriques
   - Structurer le dashboard selon la mise en page fournie

### 3. Configuration du Lever/Coucher du Soleil

- Utiliser le node moment pour formater les heures
- Intégrer les données dans le dashboard

## 💅 Personnalisation des Styles

Pour modifier l'apparence du dashboard, utiliser un node template avec le CSS suivant :

```css
<style>
    .horloge {
        /* Styles de l'horloge */
    }
    .date {
        /* Styles de la date */
    }
</style>
```

## 📚 Ressources

- Formation IoT par François Riotte
- [Documentation Node-RED](https://nodered.org/docs/)
- [Documentation OpenWeatherMap](https://openweathermap.org/api)

## 🤝 Contribution

Ce projet est un TP éducatif. Pour toute suggestion d'amélioration, merci de contacter l'équipe pédagogique.

## ⚖️ Licence

Ce projet est distribué sous licence MIT, sauf mention contraire.

---
*Crédit : Formation IoT (François Riotte)*