<p align="center">
  <img src="Designer/UIResource/TitleBar/brand/light/png/200x56/app_wordmark.png" width="360" alt="SolidDesigner" />
</p>

<p align="center">
  <a href="LICENSE"><img alt="License" src="https://img.shields.io/badge/License-GPLv3-blue.svg" /></a>
  <img alt="C++" src="https://img.shields.io/badge/C%2B%2B-17%2F20-00599C.svg" />
  <img alt="Kernel" src="https://img.shields.io/badge/Kernel-OpenCascade%20(OCCT)-orange" />
  <img alt="UI" src="https://img.shields.io/badge/UI-Qt%20Widgets-41CD52" />
  <img alt="Platform" src="https://img.shields.io/badge/Platform-Windows%20%7C%20Linux-lightgrey" />
</p>

<p align="center">
  <b>Plateforme open source de niveau industriel pour la CAO paramétrique et la conception pilotée par la simulation</b><br/>
  Modélisation basée sur les features • Modèle de données prêt pour la CAE • Architecture orientée optimisation
</p>

<p align="center">
  <img src="Docs/media/Breptera_Splash.gif" width="960" alt="Aperçu de démonstration de SolidDesigner" />
</p>

<p align="center">
  Aperçu de la démonstration du produit
</p>

## [English](README.md) | [日本語](README.ja.md) | [Français](README.fr.md) | [Deutsch](README.de.md) | [Español](README.es.md) | [Русский](README.ru.md)

> Objectif : construire un système de niveau professionnel prenant en charge la modélisation solide/surfacique, l’assemblage, la mise en plan, la mécanique des structures, la CFD, le multiphysique et l’optimisation — où les simulations peuvent piloter la conception elle-même.

---

## Quick Links

- **Tableau JIRA** : https://hananiah.atlassian.net/jira/software/c/projects/AL/boards/3
- **Wiki public (GitHub)** : https://github.com/hananiahhsu/SolidDesignerWiki
- **Wiki de conception (Confluence, accès requis)** : https://hananiah.atlassian.net/wiki/spaces/~5e2301040f45160ca25e42e3/overview?homepageId=65963

---

## Table of Contents

- [Vision et périmètre](#vision--scope)
- [Présentation du produit](#product-overview)
- [Contenu du dépôt](#whats-in-the-box)
- [Structure du projet et architecture](#project-layout--architecture)
- [Concepts clés](#core-concepts)
- [Capacités](#capabilities)
- [Feuille de route](#roadmap)
- [Compilation et exécution](#build--run)
- [Dépendances](#dependencies)
  - [Pile open source et licences](#open-source-stack--licenses)
- [Prise en main](#getting-started)
- [Plugins et scripting](#plugin--scripting)
- [Données et formats de fichiers](#data--file-formats)
- [Diagnostic, journalisation et QA](#diagnostics-logging--qa)
- [Contribution](#contributing)
- [Licence](#license)
- [Remerciements](#acknowledgments)
- [FAQ](#faq)

---

## Vision & Scope

SolidDesigner vise à devenir une plateforme CAD/CAE **full‑stack et de qualité industrielle** :

- **Parametric CAD** : modélisation robuste de pièces et d’assemblages, esquisses/contraintes, features basées sur l’historique et mise en plan.
- **CAE** : solveurs intégrés et/ou adaptateurs pour la **mécanique des structures (FEA)**, la **mécanique des fluides (CFD)** et le **multiphysique**.
- **Optimization** : optimisation **topologique / de forme / dimensionnelle**, renfort/allègement et boucles de conception pilotées par la simulation.
- **AI Assistance** : un « copilote » d’ingénierie pour l’inférence de contraintes, la détection d’intention des features, l’exploration de l’espace de conception et les suggestions de configuration de solveur.
- **Extensibility** : architecture modulaire avec une API stable pour les plugins et le scripting.

> **Status** : développement actif (pré‑alpha). Les API et formats de fichiers peuvent évoluer.

---

## Product Overview

SolidDesigner (marque : **Breptera**) est une application CAD **desktop orientée workbench**, construite sur la plateforme réutilisable **Alice**.

<p align="center">
  <img src="Docs/screenshots/home_workbench.png" width="900" alt="SolidDesigner Home Workbench" />
</p>

**Objectifs côté utilisateur**

- **Workflow** : workbenches, commandes de ruban, panneaux dockables et vues MDI.
- **Parametric foundation** : arbre d’historique des features, esquisses/contraintes, pipeline de rebuild & regeneration (WIP).
- **Engineering-first** : modèle de données CAD conçu pour porter les **matériaux, charges/BC, contrôles de maillage et résultats d’analyse** (prévu).
- **Kernel-backed geometry** : B‑Rep et visualisation par défaut via **OpenCascade (OCCT)** ; le rendu multi‑backend est pris en charge au niveau plateforme.

> La capture ci-dessus reflète la direction actuelle de l’interface (Home Workbench + panneau découverte/apprentissage). La disposition exacte évolue rapidement pendant la phase pré‑alpha.

---

## What’s in the Box

- Une base de code moderne en C++17/20 avec un **sous-module fondation (« Alice »)**.
- Une **application desktop** (« SolidDesigner ») construite sur cette fondation.
- Une séparation nette entre les couches **Core / Data / Interaction / UI**.
- Des premières implémentations du **graphe de features**, des **contraintes paramétriques**, du **diagnostic/journalisation** et de l’**hébergement de plugins**.
- Une vision à long terme pour les **solveurs CAE** (FEA/CFD) et l’**optimisation**.

---

## Project Layout & Architecture

**Physical Structure**

```
Physical Structure
    |
    |----- Alice  (submodule)
    |         |
    |         |---- Bootstrap
    |         |---- Core
    |         |---- Data
    |         |---- Interaction
    |         |---- UI
    |
    |----- SolidDesigner  (application)
              |
              |-- APP
              |-- DATA
              |-- Interaction
              |-- UI
              |-- Plugins
```

### Layered Architecture (high‑level)

- **Alice/Core** — primitives de plateforme et utilitaires de base (mémoire, threading, diagnostic, mathématiques, unités, abstractions géométriques).
- **Alice/Data** — modèle paramétrique, graphe des features/opérations, système de contraintes et dimensions, services document/session.
- **Alice/Interaction** — sélection/picking, manipulateurs, pipeline de commandes, transactions undo/redo, graphe d’interaction.
- **Alice/UI** — shell basé sur Qt (prévu), panneaux dockables, navigateur de propriétés, ruban/menus/raccourcis.
- **SolidDesigner/APP** — couche produit : cycle de vie de l’application, persistance, projet/workspace, plugins, scripting.
- **SolidDesigner/DATA/Interaction/UI** — extensions spécifiques au produit par-dessus les couches Alice.

> Le sous-module **Alice** est volontairement réutilisable et proche d’un moteur ; **SolidDesigner** l’assemble pour former un produit complet.

---

## Core Concepts

- **Feature Graph** : toutes les opérations de modélisation (Sketch, Extrude, Revolve, Fillet, Pattern, Boolean, etc.) sont des nœuds d’un graphe orienté acyclique avec **historique et dépendances**. Les rebuilds se propagent de manière déterministe.
- **Constraint System** : contraintes géométriques et dimensionnelles avec backends de solveur interchangeables (contraintes d’esquisse aujourd’hui ; contraintes 3D prévues).
- **Parametric Design** : des paramètres nommés (cotes, matériaux, conditions aux limites) peuvent piloter à la fois la géométrie et l’analyse ; prise en charge des expressions et des unités.
- **Simulation‑Driven Design** : les analyses évaluent des conceptions candidates ; les résultats sont réinjectés dans les paramètres (par ex. alléger automatiquement jusqu’à atteindre une contrainte de contrainte admissible).
- **Multi‑representation Geometry** : abstractions solide/surface/B‑Rep avec tolérances, génération de maillage pour l’analyse, cohérence CAD↔CAE.
- **Transactions** : chaque commande s’exécute dans une transaction ; undo/redo complet ; messages d’erreur pertinents via le moteur de diagnostic.

---

## Capabilities

### CAD (current/planned)

- Esquisse avec contraintes et dimensions
- Modélisation basée sur l’historique : extrusion/révolution/balayage/loft, congé/chanfrein, coque, motif, opérations booléennes
- Assemblage : mates/contraintes ; contexte top‑down (WIP)
- Mise en plan : vues, sections, dimensions, GD&T (prévu)

### CAE (current/planned)

- **Structural (FEA)** : statique linéaire, modal, bibliothèque de matériaux, conditions aux limites, contrôles de maillage (extension progressive prévue)
- **CFD** : écoulements incompressibles (stationnaires/transitoires), modèles de turbulence, conditions aux limites (prévu)
- **Multiphysics** : thermo‑mécanique, FSI (long terme)

### Optimization (planned)

- Optimisation topologique (SIMP/level‑set)
- Optimisation de forme/taille ; contraintes (contrainte, déplacement, fréquence, perte de charge, etc.)
- Exploration de l’espace de conception, modèles de substitution

### AI Assistance (planned)

- Inférence d’intention de contrainte/feature à partir des actions utilisateur
- Complétion de commandes, suggestions de paramètres
- Recommandations d’espace de conception, DOE automatique
- Suggestions de configuration de solveur et de maillage selon le contexte

> Voir **[Roadmap](#roadmap)** et **JIRA** pour le suivi détaillé des éléments.

---

## Roadmap

La planification et le backlog sont suivis dans **JIRA** :  
https://hananiah.atlassian.net/jira/software/c/projects/AL/boards/3

Jalons de haut niveau (susceptibles d’évoluer) :

1. **P0 — Modeling Foundations** : graphe de features stable, sketcher robuste, opérations de modélisation cœur, système de transactions, persistance.
2. **P1 — Meshing & FEA MVP** : pipeline de maillage tétra/hexa ; statique linéaire/modal ; post‑traitement de base.
3. **P2 — CFD MVP** : intégration maillage + solveur pour les écoulements incompressibles ; champs pression/vitesse/température ; post‑traitement.
4. **P3 — Optimization** : optimisation topologique SIMP ; mise à jour paramétrique en boucle fermée ; gestion des contraintes.
5. **P4 — AI Copilot v1** : inférence de contraintes, suggestions de commandes, préréglages solveur ; apprentissage à partir de l’historique des projets.

Les documents de conception détaillés se trouvent dans **Confluence** (accès requis). Un sous-ensemble public est disponible dans le **Wiki GitHub**.

---

## Build & Run

Ce dépôt fournit des **scripts de build en un clic** qui génèrent un arbre de build sous `../SolidDesigner_Build/`.

### Prerequisites (current)

- **CMake ≥ 3.31**  
  - Windows : le dépôt embarque CMake sous `ToolChain/cmake` (utilisé par `AutoGenerateVsProject.bat`)  
  - Linux : installez une version récente de CMake sur le système (ou utilisez votre propre toolchain)
- **C++17 toolchain** : MSVC v143 / GCC 11+ / Clang 15+
- **Qt 5.15.x** avec les modules : Core, Gui, Widgets, Network, Quick, Qml
- **OpenCascade (OCCT) SDK** pour le backend de visualisation OCCT (voir la disposition SDK ci-dessous)

### Windows (Visual Studio 2022, x64)

1. Cloner avec les sous-modules :

```bash
git clone --recurse-submodules https://github.com/hananiahhsu/SolidDesigner.git
cd SolidDesigner
```

2. Exécuter :

- `AutoGenerateVsProject.bat` (génère `../SolidDesigner_Build/SolidDesigner.sln` et ouvre Visual Studio)

3. Compiler la configuration `Release|x64` dans Visual Studio, puis lancer `SolidDesigner`.

### Linux (Makefiles)

Exécuter :

```bash
./SolidDesignerForLinux.sh
```

Ce script configure et compile avec `Unix Makefiles`, puis écrit la sortie dans `../SolidDesigner_Build/`.

> Remarque : le script passe actuellement `-DCMAKE_GENERATOR_PLATFORM=x64`, qui est une option Visual Studio et peut être ignorée par les toolchains Linux. En cas de problème, exécutez CMake manuellement (section suivante).

### Manual CMake (recommended when customizing toolchains)

```bash
cmake -S . -B ../SolidDesigner_Build -G "Ninja" -DCMAKE_BUILD_TYPE=Release
cmake --build ../SolidDesigner_Build --parallel
```

### Third‑party SDK layout (OCCT)

Le backend de visualisation OCCT attend que le SDK OpenCascade soit exporté vers :

```
Externals/3rdParty/sdk/<platform>/<Debug|Release>/occt
```

Valeurs par défaut de `<platform>` (surchargables) :

- Windows : `msvc2022-x64-md`
- Linux : `linux-x64`

Vous pouvez surcharger depuis CMake :

- `-DSD_3P_PLATFORM=...`
- `-DSD_3P_CFG=Debug|Release`
- ou pointer directement `-DOpenCASCADE_DIR=...` vers le dossier contenant `OpenCASCADEConfig.cmake`.

### Qt

Les cibles UI utilisent actuellement **Qt 5** (par ex. `Qt5::Core`, `Qt5::Widgets`, `Qt5::Quick/Qml` dans CMake).  
Sous Windows, certains modules définissent un `CMAKE_PREFIX_PATH` par défaut pour `Qt5.15.x` ; adaptez-le à votre installation locale de Qt si nécessaire.

---

## Dependencies

Le projet est modulaire : certaines bibliothèques sont **vendorisées dans l’arborescence**, tandis que d’autres sont attendues comme **SDK externes**.

### Open-source Stack & Licenses

| Bibliothèque | Usage | Emplacement | Licence (amont) |
|---|---|---|---|
| **OpenCascade (OCCT)** | Noyau B‑Rep + backend de visualisation OCCT | `Alice/Core/Runtime/AliceRenderBackendOCCViewer` | LGPL‑2.1 with OCCT exception (amont) |
| **Qt 5 (Widgets/Quick/Qml)** | UI desktop (ruban, panneaux, boîtes de dialogue) | `Designer/UI/*`, `Alice/UI/QFrameWork/*` | GPL/LGPL/commercial (Qt) |
| **spdlog** | Backend de journalisation | `Alice/Core/Foundation/AliceBasicTool/*SpdLog*` | MIT |
| **fmt** | Formatage de chaînes | `Alice/Core/Foundation/AliceBasicTool/*Fmt*` | MIT |
| **Open Sans** | Polices UI pour le ruban | `Alice/UI/QFrameWork/AliceRibbon/OpenSans` | Apache‑2.0 |
| | | | |
| | | | |

> **Note de licence** : SolidDesigner est sous **GPLv3**, mais certaines dépendances intégrées/requises sont sous LGPL/MIT/Apache. Lors de la distribution de binaires, vous devez respecter chaque licence amont (obligations de liaison dynamique, notices, disponibilité des sources, etc.).

### Optional / planned adapters (not required for a minimal build)

- Des backends de rendu **OGRE / OSG / VTK / Skylark** existent comme modules plateforme (`Alice/Core/Runtime/AliceRenderBackend*`), mais peuvent nécessiter des SDK supplémentaires et restent en évolution.
- Les **mailleurs / solveurs** (FEA/CFD/optimisation) sont en cours de conception active ; des adaptateurs seront introduits progressivement.

---

## Getting Started

Flux de travail typique visé (état cible) :

1. **Créer un projet** et définir les unités/tolérances par défaut.
2. **Esquisser** sur un plan ; utiliser contraintes/dimensions.
3. Créer des features : **Extrude**, **Revolve**, **Fillet**, **Shell**, **Pattern**…
4. **Assembler** les pièces ; ajouter mates/contraintes.
5. **Mailler** le modèle (contrôles globaux + locaux).
6. Définir les **matériaux** et les **conditions aux limites**.
7. Exécuter la **FEA/CFD** ; inspecter contraintes/déformations, modes, champs d’écoulement.
8. **Piloter les paramètres** à partir des résultats (par ex. réduire l’épaisseur jusqu’à ce que la contrainte ≤ la cible).
9. Enregistrer comme **projet** et exporter en **STEP/IGES** ou formats de maillage.

---

## Plugin & Scripting

- **Plugin ABI** : interfaces C++ propres pour les opérations géométriques, le maillage, les solveurs, les importeurs/exporteurs et les add-ins UI.
- **Isolation** : modèle de possession stable et sécurité inter-DLL (la fondation fournit des utilitaires de pointeurs Owning/Weak/Guard).
- **Scripting (planned)** : API Python pour automatiser la modélisation, configurer des études, post-traiter les résultats et orchestrer les boucles de conception.
- **AI hooks (planned)** : enregistrement de conseillers de conception personnalisés et de modèles ML pour la prédiction d’intention et l’optimisation.

---

## Data & File Formats

### Native project format (in progress)

Le format natif est conçu pour être :

- **Structured** : métadonnées + charges utiles typées (géométrie, maillage, résultats, vignettes, etc.)
- **Versioned** : versionnage de schéma avec pipeline explicite de migration
- **Incremental-friendly** : conçu pour le rechargement partiel et de futurs workflows cloud/workspace
- **Stable-identity aware** : les IDs d’objets survivent au save/load, au copier/coller et aux migrations

> Le wiki public hébergera la spécification canonique une fois le format stabilisé.

### Interoperability (planned / incremental)

- **CAD Interop** : import/export STEP/IGES (autres formats via adaptateurs)
- **Mesh/Results** : formats standard de maillage/résultats pour solveurs externes et post-traitement (VTK, MED, etc., prévu)
- **Units** : système d’unités cohérent avec métadonnées explicites ; paramètres dimensionnés dans les expressions

---

## Diagnostics, Logging & QA

- **DiagnosticsEngine** unifié avec niveaux de sévérité, emplacements source et sinks enfichables (console, fichier, panneau UI).
- Backend **spdlog** optionnel pour une journalisation rapide et thread-aware.
- **Assertions** et **vérifications défensives** aux frontières entre DLL.
- **Tests** via CTest ; jeux de tests pour la géométrie, le maillage et la validité des solveurs ; cas reproductibles joints à JIRA.

---

## Contributing

Les contributions sont les bienvenues.

- Consultez les epics/tâches JIRA et le Wiki GitHub pour le contexte.
- Discutez des propositions importantes avant d’ouvrir une PR.
- Respectez le style de code du projet (fichier clang-format prévu) et ajoutez des tests unitaires.
- Gardez des commits petits et bien décrits ; liez-les aux tickets JIRA quand c’est pertinent.

Premières contributions suggérées :

- Corriger des problèmes de build sur une plateforme/un compilateur spécifique
- Ajouter des tests ciblés (géométrie, persistance, résolution de contraintes)
- Ajouter de la documentation : notes de conception, diagrammes, ou sections minimales « how it works »

> Documents contributeur au niveau dépôt (prévus) : `CONTRIBUTING.md`, `CODE_OF_CONDUCT.md`.

---

## License

Ce dépôt est distribué sous **GNU GPL v3.0**. Voir `LICENSE` pour le texte complet.

> Remarque : les bibliothèques tierces peuvent avoir leurs propres licences ; assurez-vous de la conformité lors de la redistribution de binaires.

---

## Acknowledgments

Ce projet repose sur les épaules de géants : OpenCascade, Eigen, fmt, spdlog, Qt et la communauté open source au sens large.  
Un grand merci aux contributeurs et chercheurs du domaine CAD/CAE/CFD/optimisation.

---

## FAQ

**Existe-t-il une API de scripting ?**  
Une API Python est prévue. Une première ossature interne existe ; l’API publique arrive prochainement.

**Quelle pile de solveurs est utilisée ?**  
Des solveurs internes sont en cours de prototypage. Des adaptateurs vers des solveurs externes (mailleurs/post, par ex.) sont prévus.

**Les fonctionnalités IA nécessiteront-elles un accès internet ?**  
Non. L’objectif est de prendre en charge une inférence hors ligne avec des modèles locaux, avec des intégrations cloud optionnelles.

**Où puis-je suivre l’avancement ?**  
JIRA (roadmap/backlog) et le Wiki GitHub public. Les documents de conception détaillés se trouvent dans Confluence (accès requis).
