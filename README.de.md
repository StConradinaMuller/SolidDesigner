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
  <b>Open-Source-Plattform in Engineering-Qualität für parametrisches CAD und simulationsgetriebenes Design</b><br/>
  Feature-basierte Modellierung • CAE-fähiges Datenmodell • Optimierungsorientierte Architektur
</p>

<p align="center">
  <img src="Docs/media/Breptera_Splash.gif" width="960" alt="SolidDesigner Demo-Vorschau" />
</p>

<p align="center">
  Produkt-Demo-Vorschau
</p>

## [English](README.md) | [日本語](README.ja.md) | [Français](README.fr.md) | [Deutsch](README.de.md) | [Español](README.es.md) | [Русский](README.ru.md)

> Ziel: ein professionelles System, das Solid-/Flächenmodellierung, Baugruppen, Zeichnungserstellung, Strukturmechanik, CFD, Multiphysik und Optimierung unterstützt — so dass Simulationen das Design selbst treiben können.

---

## Quick Links

- **JIRA-Board**: https://hananiah.atlassian.net/jira/software/c/projects/AL/boards/3
- **Öffentliches Wiki (GitHub)**: https://github.com/hananiahhsu/SolidDesignerWiki
- **Design-Wiki (Confluence, Zugriff erforderlich)**: https://hananiah.atlassian.net/wiki/spaces/~5e2301040f45160ca25e42e3/overview?homepageId=65963

---

## Table of Contents

- [Vision & Umfang](#vision--scope)
- [Produktüberblick](#product-overview)
- [Was enthalten ist](#whats-in-the-box)
- [Projektstruktur & Architektur](#project-layout--architecture)
- [Kernkonzepte](#core-concepts)
- [Fähigkeiten](#capabilities)
- [Roadmap](#roadmap)
- [Build & Run](#build--run)
- [Abhängigkeiten](#dependencies)
  - [Open-Source-Stack & Lizenzen](#open-source-stack--licenses)
- [Erste Schritte](#getting-started)
- [Plugins & Scripting](#plugin--scripting)
- [Daten & Dateiformate](#data--file-formats)
- [Diagnostik, Logging & QA](#diagnostics-logging--qa)
- [Beitragen](#contributing)
- [Lizenz](#license)
- [Danksagungen](#acknowledgments)
- [FAQ](#faq)

---

## Vision & Scope

SolidDesigner soll eine **Full-Stack-CAD/CAE-Plattform in Engineering-Qualität** werden:

- **Parametric CAD**: robuste Teile-/Baugruppenmodellierung, Skizzen/Constraints, historie-basierte Features und Zeichnungserstellung.
- **CAE**: integrierte Solver und/oder Adapter für **Strukturmechanik (FEA)**, **Strömungsmechanik (CFD)** und **Multiphysik**.
- **Optimization**: **Topologie-/Form-/Größenoptimierung**, Verstärkung/Gewichtsreduktion und simulationsgetriebene Designschleifen.
- **AI Assistance**: ein Engineering-„Copilot“ für Constraint-Inferenz, Feature-Intent-Erkennung, Design-Space-Exploration und Vorschläge zur Solver-Konfiguration.
- **Extensibility**: modulare Architektur mit stabiler Plugin- und Scripting-API.

> **Status**: aktive Entwicklung (Pre-Alpha). APIs und Dateiformate können sich ändern.

---

## Product Overview

SolidDesigner (Marke: **Breptera**) ist eine **Desktop-CAD-Anwendung mit Workbench-Ausrichtung**, aufgebaut auf der wiederverwendbaren **Alice**-Plattform.

<p align="center">
  <img src="Docs/screenshots/home_workbench.png" width="900" alt="SolidDesigner Home Workbench" />
</p>

**Ziele aus Nutzersicht**

- **Workflow**: Workbenches, Ribbon-Befehle, andockbare Panels und MDI-Viewports.
- **Parametric foundation**: Feature-History-Baum, Skizzen/Constraints, Rebuild- & Regenerationspipeline (WIP).
- **Engineering-first**: CAD-Datenmodell, ausgelegt zum Tragen von **Materialien, Lasten/BCs, Netzsteuerungen und Analyseergebnissen** (geplant).
- **Kernel-backed geometry**: Standard-B-Rep und Visualisierung über **OpenCascade (OCCT)**; Multi-Backend-Rendering wird auf Plattformebene unterstützt.

> Der Screenshot oben zeigt die aktuelle UI-Richtung (Home Workbench + Discovery/Learning-Panel). Das genaue Layout ändert sich in der Pre-Alpha-Phase schnell.

---

## What’s in the Box

- Eine moderne C++17/20-Codebasis mit einem **Foundation-Submodul („Alice“)**.
- Eine darauf aufbauende **Desktop-Anwendung** („SolidDesigner“).
- Eine saubere Trennung zwischen den Schichten **Core / Data / Interaction / UI**.
- Frühe Implementierungen von **Feature-Graph**, **parametrischen Constraints**, **Diagnostik/Logging** und **Plugin-Hosting**.
- Eine langfristige Planung für **CAE-Solver** (FEA/CFD) und **Optimierung**.

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

- **Alice/Core** — Plattformprimitiven und Basis-Utilities (Speicher, Threading, Diagnostik, Mathematik, Einheiten, Geometrieabstraktionen).
- **Alice/Data** — parametrisches Modell, Feature-/Operationsgraph, Constraint- & Bemaßungssystem, Dokument-/Session-Services.
- **Alice/Interaction** — Auswahl/Picking, Manipulatoren, Command-Pipeline, Undo/Redo-Transaktionen, Interaktionsgraph.
- **Alice/UI** — Qt-basierte (geplante) Shell, dockbare Bereiche, Property-Browser, Ribbon/Menüs/Shortcuts.
- **SolidDesigner/APP** — die Produktebene: Anwendungslebenszyklus, Persistenz, Projekt/Workspace, Plugins, Scripting.
- **SolidDesigner/DATA/Interaction/UI** — produktspezifische Erweiterungen über den Alice-Schichten.

> Das **Alice**-Submodul ist bewusst wiederverwendbar und engine-artig ausgelegt; **SolidDesigner** komponiert daraus ein vollständiges Produkt.

---

## Core Concepts

- **Feature Graph**: Alle Modellierungsoperationen (Sketch, Extrude, Revolve, Fillet, Pattern, Boolean usw.) sind Knoten in einem gerichteten azyklischen Graphen mit **Historie und Abhängigkeiten**. Rebuilds propagieren deterministisch.
- **Constraint System**: geometrische und dimensionale Constraints mit Solver-Backends (heute Skizzen-Constraints; 3D-Constraints geplant).
- **Parametric Design**: benannte Parameter (Maße, Materialien, Randbedingungen) können sowohl Geometrie als auch Analyse treiben; unterstützt Ausdrücke und Einheiten.
- **Simulation‑Driven Design**: Analysen bewerten Designkandidaten; Ergebnisse fließen in Parameter zurück (z. B. automatische Gewichtsreduktion bis Spannungsziele erfüllt sind).
- **Multi‑representation Geometry**: Solid-/Surface-/B-Rep-Abstraktionen mit Toleranzen, Netzerzeugung für Analysen, CAD↔CAE-Konsistenz.
- **Transactions**: Jeder Befehl läuft in einer Transaktion; vollständiges Undo/Redo; aussagekräftige Fehlermeldungen über die Diagnostik-Engine.

---

## Capabilities

### CAD (current/planned)

- Skizzieren mit Constraints und Bemaßungen
- Historienbasierte Modellierung: Extrude/Revolve/Sweep/Loft, Fillet/Chamfer, Shell, Pattern, Boolesche Operationen
- Baugruppe: Mates/Constraints; Top-down-Kontext (WIP)
- Zeichnung: Ansichten, Schnitte, Bemaßungen, GD&T (geplant)

### CAE (current/planned)

- **Structural (FEA)**: lineare Statik, Modal; Materialbibliothek; Randbedingungen; Netzsteuerungen (schrittweise Erweiterung geplant)
- **CFD**: inkompressible Strömungen (stationär/transient); Turbulenzmodelle; Randbedingungen (geplant)
- **Multiphysics**: Thermo-Struktur, FSI (langfristig)

### Optimization (planned)

- Topologieoptimierung (SIMP/Level-Set)
- Form-/Größenoptimierung; Constraints (Spannung, Verschiebung, Frequenz, Druckverlust usw.)
- Design-Space-Exploration; Surrogatmodelle

### AI Assistance (planned)

- Constraint-/Feature-Intent-Inferenz aus Benutzeraktionen
- Befehlsvervollständigung, Parametervorschläge
- Empfehlungen für den Designraum, automatisches DOE
- Vorschläge für Solver-Setup und Meshing abhängig vom Kontext

> Detaillierten Fortschritt auf Elementebene finden Sie in **[Roadmap](#roadmap)** und **JIRA**.

---

## Roadmap

Planung und Backlog werden in **JIRA** verfolgt:  
https://hananiah.atlassian.net/jira/software/c/projects/AL/boards/3

Übergeordnete Meilensteine (Änderungen vorbehalten):

1. **P0 — Modeling Foundations**: stabiler Feature-Graph, robuster Sketcher, Kern-Modellieroperationen, Transaktionssystem, Persistenz.
2. **P1 — Meshing & FEA MVP**: Tet/Hex-Mesh-Pipeline; lineare Statik/Modal; grundlegendes Post-Processing.
3. **P2 — CFD MVP**: Mesh- und Solver-Integration für inkompressible Strömungen; Druck-/Geschwindigkeits-/Temperaturfelder; Post-Processing.
4. **P3 — Optimization**: SIMP-Topologieoptimierung; geschlossene Parameter-Updates; Constraint-Handling.
5. **P4 — AI Copilot v1**: Constraint-Inferenz, Command-Vorschläge, Solver-Presets; Lernen aus Projekthistorie.

Detaillierte Designdokumente liegen in **Confluence** (Zugriff erforderlich). Eine öffentliche Teilmenge liegt im **GitHub-Wiki**.

---

## Build & Run

Dieses Repo enthält **One-Click-Build-Skripte**, die einen Build-Baum unter `../SolidDesigner_Build/` erzeugen.

### Prerequisites (current)

- **CMake ≥ 3.31**  
  - Windows: Das Repo bündelt CMake unter `ToolChain/cmake` (genutzt von `AutoGenerateVsProject.bat`)  
  - Linux: Installieren Sie eine aktuelle Systemversion von CMake (oder verwenden Sie Ihre eigene Toolchain)
- **C++17 toolchain**: MSVC v143 / GCC 11+ / Clang 15+
- **Qt 5.15.x** mit den Modulen: Core, Gui, Widgets, Network, Quick, Qml
- **OpenCascade (OCCT) SDK** für das OCCT-Viewer-Backend (siehe SDK-Layout unten)

### Windows (Visual Studio 2022, x64)

1. Mit Submodulen klonen:

```bash
git clone --recurse-submodules https://github.com/hananiahhsu/SolidDesigner.git
cd SolidDesigner
```

2. Ausführen:

- `AutoGenerateVsProject.bat` (erzeugt `../SolidDesigner_Build/SolidDesigner.sln` und öffnet Visual Studio)

3. Die Konfiguration `Release|x64` in Visual Studio bauen und anschließend `SolidDesigner` starten.

### Linux (Makefiles)

Ausführen:

```bash
./SolidDesignerForLinux.sh
```

Dieses Skript konfiguriert und baut mit `Unix Makefiles` und schreibt die Ausgabe nach `../SolidDesigner_Build/`.

> Hinweis: Das Skript übergibt derzeit `-DCMAKE_GENERATOR_PLATFORM=x64`. Das ist eine Visual-Studio-Option und kann unter Linux ignoriert werden. Falls Probleme auftreten, führen Sie CMake manuell aus (nächster Abschnitt).

### Manual CMake (recommended when customizing toolchains)

```bash
cmake -S . -B ../SolidDesigner_Build -G "Ninja" -DCMAKE_BUILD_TYPE=Release
cmake --build ../SolidDesigner_Build --parallel
```

### Third‑party SDK layout (OCCT)

Das OCCT-Viewer-Backend erwartet, dass das OpenCascade-SDK hier exportiert ist:

```
Externals/3rdParty/sdk/<platform>/<Debug|Release>/occt
```

Standardwerte für `<platform>` (überschreibbar):

- Windows: `msvc2022-x64-md`
- Linux: `linux-x64`

Sie können dies aus CMake heraus überschreiben:

- `-DSD_3P_PLATFORM=...`
- `-DSD_3P_CFG=Debug|Release`
- oder direkt `-DOpenCASCADE_DIR=...` auf den Ordner zeigen lassen, der `OpenCASCADEConfig.cmake` enthält.

### Qt

Die UI-Targets verwenden derzeit **Qt 5** (z. B. `Qt5::Core`, `Qt5::Widgets`, `Qt5::Quick/Qml` in CMake).  
Unter Windows setzen einige Module einen Standard-`CMAKE_PREFIX_PATH` für `Qt5.15.x`; passen Sie ihn bei Bedarf an Ihre lokale Qt-Installation an.

---

## Dependencies

Das Projekt ist modular: einige Bibliotheken sind **im Baum vendored**, andere werden als **externe SDKs** erwartet.

### Open-source Stack & Licenses

| Bibliothek | Verwendungszweck | Ort | Lizenz (Upstream) |
|---|---|---|---|
| **OpenCascade (OCCT)** | B-Rep-Kernel + OCCT-Viewer-Backend | `Alice/Core/Runtime/AliceRenderBackendOCCViewer` | LGPL‑2.1 mit OCCT exception (Upstream) |
| **Qt 5 (Widgets/Quick/Qml)** | Desktop-UI (Ribbon, Panels, Dialoge) | `Designer/UI/*`, `Alice/UI/QFrameWork/*` | GPL/LGPL/commercial (Qt) |
| **spdlog** | Logging-Backend | `Alice/Core/Foundation/AliceBasicTool/*SpdLog*` | MIT |
| **fmt** | String-Formatierung | `Alice/Core/Foundation/AliceBasicTool/*Fmt*` | MIT |
| **Open Sans** | UI-Schriftassets für das Ribbon | `Alice/UI/QFrameWork/AliceRibbon/OpenSans` | Apache‑2.0 |
| | | | |
| | | | |

> **Lizenzhinweis**: SolidDesigner steht unter **GPLv3**, aber einige eingebettete/erforderliche Abhängigkeiten stehen unter LGPL/MIT/Apache. Beim Verteilen von Binärdateien müssen Sie die jeweiligen Upstream-Lizenzen einhalten (Pflichten zu dynamischem Linken, Hinweise, Quellverfügbarkeit usw.).

### Optional / planned adapters (not required for a minimal build)

- **OGRE / OSG / VTK / Skylark**-Render-Backends existieren als Plattformmodule (`Alice/Core/Runtime/AliceRenderBackend*`), können aber zusätzliche SDKs erfordern und befinden sich noch in Entwicklung.
- **Meshing / Solver** (FEA/CFD/Optimierung) werden aktiv entworfen; Adapter werden schrittweise eingeführt.

---

## Getting Started

Typischer Ziel-Workflow (Endzustand):

1. **Projekt anlegen** und Standard-Einheiten/Toleranzen festlegen.
2. Auf einer Ebene **skizzieren**; Constraints/Bemaßungen anwenden.
3. Features erzeugen: **Extrude**, **Revolve**, **Fillet**, **Shell**, **Pattern** …
4. Teile **zusammenbauen**; Mates/Constraints hinzufügen.
5. Das Modell **vernetzen** (globale + lokale Steuerungen).
6. **Materialien** und **Randbedingungen** definieren.
7. **FEA/CFD** ausführen; Spannungen/Dehnungen, Modi und Strömungsfelder auswerten.
8. **Parameter aus Ergebnissen treiben** (z. B. Dicke reduzieren, bis Spannung ≤ Zielwert).
9. Als **Projekt** speichern und nach **STEP/IGES** oder Mesh-Formaten exportieren.

---

## Plugin & Scripting

- **Plugin ABI**: saubere C++-Schnittstellen für Geometrieoperationen, Meshing, Solver, Importe/Exporte und UI-Add-ins.
- **Isolation**: stabiles Ownership-Modell und Cross-DLL-Sicherheit (die Foundation stellt Owning/Weak/Guard-Pointer-Utilities bereit).
- **Scripting (planned)**: Python-API zur Automatisierung der Modellierung, Einrichtung von Studien, Nachbearbeitung von Ergebnissen und Orchestrierung von Designschleifen.
- **AI hooks (planned)**: Registrierung benutzerdefinierter Design-Berater und ML-Modelle für Intent-Vorhersage und Optimierung.

---

## Data & File Formats

### Native project format (in progress)

Das native Format soll folgende Eigenschaften haben:

- **Structured**: Metadaten + typisierte Payloads (Geometrie, Mesh, Ergebnisse, Thumbnails usw.)
- **Versioned**: Schema-Versionierung mit expliziter Upgrade-Pipeline
- **Incremental-friendly**: für partielles Reloading und künftige Cloud-/Workspace-Workflows ausgelegt
- **Stable-identity aware**: Objekt-IDs überleben Save/Load, Copy/Paste und Upgrades

> Das öffentliche Wiki wird die kanonische Spezifikation hosten, sobald das Format stabil ist.

### Interoperability (planned / incremental)

- **CAD Interop**: STEP/IGES-Import/Export (weitere Formate über Adapter)
- **Mesh/Results**: Standard-Mesh-/Ergebnisformate für externe Solver/Post (VTK, MED usw., geplant)
- **Units**: konsistentes Einheitensystem mit expliziten Metadaten; dimensionierte Parameter in Ausdrücken

---

## Diagnostics, Logging & QA

- Vereinheitlichte **DiagnosticsEngine** mit Schweregraden, Quellpositionen und austauschbaren Sinks (Konsole, Datei, UI-Panel).
- Optionales **spdlog**-Backend für schnelles, thread-aware Logging.
- **Assertions** und **defensive Prüfungen** über DLL-Grenzen hinweg.
- **Tests** via CTest; Fixtures für Geometrie, Meshing und Solver-Korrektheit; reproduzierbare Fälle werden an JIRA angehängt.

---

## Contributing

Beiträge sind willkommen.

- Prüfen Sie JIRA-Epics/Tasks und das GitHub-Wiki für den Kontext.
- Diskutieren Sie größere Vorschläge, bevor Sie eine PR öffnen.
- Befolgen Sie den Code-Stil des Projekts (clang-format-Datei geplant) und fügen Sie Unit-Tests hinzu.
- Halten Sie Commits klein und gut beschrieben; verlinken Sie nach Möglichkeit JIRA-Tickets.

Empfohlene erste Beiträge:

- Build-Probleme auf einer bestimmten Plattform/einem bestimmten Compiler beheben
- Fokussierte Tests hinzufügen (Geometrie, Persistenz, Constraint-Lösung)
- Dokumentation ergänzen: Design-Notizen, Diagramme oder kurze „How it works“-Abschnitte

> Repository-weite Contributor-Dokumente (geplant): `CONTRIBUTING.md`, `CODE_OF_CONDUCT.md`.

---

## License

Dieses Repository ist unter **GNU GPL v3.0** lizenziert. Den vollständigen Text finden Sie in `LICENSE`.

> Hinweis: Drittanbieterbibliotheken können eigene Lizenzen haben; achten Sie auf Compliance beim Weiterverteilen von Binärdateien.

---

## Acknowledgments

Dieses Projekt steht auf den Schultern von Giganten: OpenCascade, Eigen, fmt, spdlog, Qt und der breiteren Open-Source-Community.  
Besonderer Dank gilt den Mitwirkenden und Forschenden in CAD/CAE/CFD/Optimierung.

---

## FAQ

**Gibt es eine Scripting-API?**  
Eine Python-API ist geplant. Frühe interne Vorarbeiten existieren bereits; die öffentliche API folgt.

**Welcher Solver-Stack wird verwendet?**  
Frühe Inhouse-Solver werden derzeit prototypisch entwickelt. Adapter zu externen Solver-Stacks (z. B. Mesher/Post) sind geplant.

**Benötigen KI-Funktionen Internetzugang?**  
Nein. Geplant ist die Unterstützung lokaler Offline-Inferenz mit optionalen Cloud-Integrationen.

**Wo kann ich den Fortschritt verfolgen?**  
JIRA (Roadmap/Backlog) und das öffentliche GitHub-Wiki. Detaillierte Design-Dokumente liegen in Confluence (Zugriff erforderlich).
