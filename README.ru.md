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
  <b>Открытая платформа инженерного класса для параметрического CAD и проектирования, управляемого моделированием</b><br/>
  Моделирование на основе features • Модель данных, готовая к CAE • Архитектура, ориентированная на оптимизацию
</p>

<p align="center">
  <img src="Docs/media/breptera_splash.apng" width="960" alt="Предпросмотр демо SolidDesigner" />
</p>

<p align="center">
  Предпросмотр демонстрации продукта
</p>

## [English](README.md) | [日本語](README.ja.md) | [Français](README.fr.md) | [Deutsch](README.de.md) | [Español](README.es.md) | [Русский](README.ru.md)

> Цель: профессиональная система, поддерживающая твердотельное/поверхностное моделирование, сборки, черчение, механику конструкций, CFD, мультифизику и оптимизацию — где симуляции могут управлять самим проектированием.

---

## Quick Links

- **Доска JIRA**: https://hananiah.atlassian.net/jira/software/c/projects/AL/boards/3
- **Публичная wiki (GitHub)**: https://github.com/hananiahhsu/SolidDesignerWiki
- **Wiki по проектированию (Confluence, требуется доступ)**: https://hananiah.atlassian.net/wiki/spaces/~5e2301040f45160ca25e42e3/overview?homepageId=65963

---

## Table of Contents

- [Видение и область охвата](#vision--scope)
- [Обзор продукта](#product-overview)
- [Что входит в состав](#whats-in-the-box)
- [Структура проекта и архитектура](#project-layout--architecture)
- [Ключевые концепции](#core-concepts)
- [Возможности](#capabilities)
- [Дорожная карта](#roadmap)
- [Сборка и запуск](#build--run)
- [Зависимости](#dependencies)
  - [Open-source стек и лицензии](#open-source-stack--licenses)
- [Быстрый старт](#getting-started)
- [Плагины и скриптинг](#plugin--scripting)
- [Данные и форматы файлов](#data--file-formats)
- [Диагностика, логирование и QA](#diagnostics-logging--qa)
- [Участие в проекте](#contributing)
- [Лицензия](#license)
- [Благодарности](#acknowledgments)
- [FAQ](#faq)

---

## Vision & Scope

SolidDesigner стремится стать **full‑stack платформой CAD/CAE инженерного уровня**:

- **Parametric CAD**: надежное моделирование деталей и сборок, эскизы/ограничения, features на основе истории и выпуск чертежей.
- **CAE**: встроенные решатели и/или адаптеры для **механики конструкций (FEA)**, **гидродинамики (CFD)** и **мультифизики**.
- **Optimization**: **топологическая / формообразующая / размерная** оптимизация, усиление/снижение массы и циклы проектирования, управляемые расчетом.
- **AI Assistance**: инженерный «копилот» для вывода ограничений, определения намерения features, исследования пространства решений и подсказок по настройке решателей.
- **Extensibility**: модульная архитектура со стабильным API для плагинов и скриптинга.

> **Status**: активная разработка (pre‑alpha). API и форматы файлов могут меняться.

---

## Product Overview

SolidDesigner (бренд: **Breptera**) — это **настольное CAD-приложение, ориентированное на workbench-подход**, построенное на повторно используемой платформе **Alice**.

<p align="center">
  <img src="Docs/screenshots/home_workbench.png" width="900" alt="SolidDesigner Home Workbench" />
</p>

**Цели с точки зрения пользователя**

- **Workflow**: workbench-режимы, ribbon-команды, dockable-панели и MDI-viewports.
- **Parametric foundation**: дерево истории features, sketches/constraints, pipeline rebuild & regeneration (WIP).
- **Engineering-first**: CAD-модель данных, рассчитанная на хранение **материалов, нагрузок/BC, настроек сетки и результатов расчета** (планируется).
- **Kernel-backed geometry**: B‑Rep и визуализация по умолчанию через **OpenCascade (OCCT)**; на уровне платформы поддерживается несколько backend’ов рендеринга.

> Скриншот выше отражает текущее направление интерфейса (Home Workbench + панель discovery/learning). Точное расположение элементов быстро меняется в pre‑alpha.

---

## What’s in the Box

- Современная кодовая база на C++17/20 с **foundation-подмодулем («Alice»)**.
- **Настольное приложение** («SolidDesigner»), построенное поверх foundation-уровня.
- Четкое разделение между слоями **Core / Data / Interaction / UI**.
- Ранние реализации **графа features**, **параметрических ограничений**, **диагностики/логирования** и **хостинга плагинов**.
- Долгосрочный план по **CAE-решателям** (FEA/CFD) и **оптимизации**.

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

- **Alice/Core** — платформенные примитивы и базовые утилиты (память, потоки, диагностика, математика, единицы, геометрические абстракции).
- **Alice/Data** — параметрическая модель, граф features/операций, система ограничений и размеров, сервисы документа/сессии.
- **Alice/Interaction** — выбор/picking, манипуляторы, командный pipeline, транзакции undo/redo, граф взаимодействия.
- **Alice/UI** — оболочка на Qt (планируется), dockable-панели, браузер свойств, ribbon/меню/горячие клавиши.
- **SolidDesigner/APP** — уровень продукта: жизненный цикл приложения, персистентность, проект/workspace, плагины, скриптинг.
- **SolidDesigner/DATA/Interaction/UI** — продуктовые расширения поверх слоев Alice.

> Подмодуль **Alice** намеренно сделан переиспользуемым и engine-подобным; **SolidDesigner** композитно собирает из него полноценный продукт.

---

## Core Concepts

- **Feature Graph**: все операции моделирования (Sketch, Extrude, Revolve, Fillet, Pattern, Boolean и т. д.) представлены узлами ориентированного ациклического графа с **историей и зависимостями**. Перестроение распространяется детерминированно.
- **Constraint System**: геометрические и размерные ограничения с backend’ами решателя (сейчас — ограничения эскиза; 3D-ограничения планируются).
- **Parametric Design**: именованные параметры (размеры, материалы, граничные условия) могут управлять и геометрией, и расчетом; поддерживаются выражения и единицы измерения.
- **Simulation‑Driven Design**: анализы оценивают варианты конструкции; результаты возвращаются в параметры (например, автоматически уменьшать массу до выполнения требования по напряжениям).
- **Multi‑representation Geometry**: абстракции solid/surface/B‑Rep с учетом допусков, генерация сетки для анализа, согласованность CAD↔CAE.
- **Transactions**: каждая команда выполняется внутри транзакции; полный undo/redo; понятные сообщения об ошибках через движок диагностики.

---

## Capabilities

### CAD (current/planned)

- Эскизирование с ограничениями и размерами
- Историческое моделирование: extrude/revolve/sweep/loft, fillet/chamfer, shell, pattern, булевы операции
- Сборки: mates/constraints; top‑down context (WIP)
- Чертежи: виды, сечения, размеры, GD&T (планируется)

### CAE (current/planned)

- **Structural (FEA)**: линейная статика, модальный анализ; библиотека материалов; граничные условия; управление сеткой (планируется поэтапное расширение)
- **CFD**: несжимаемые потоки (стационарные/нестационарные); модели турбулентности; граничные условия (планируется)
- **Multiphysics**: термо‑структурная связка, FSI (долгосрочно)

### Optimization (planned)

- Топологическая оптимизация (SIMP/level‑set)
- Оптимизация формы/размера; ограничения (напряжение, перемещение, частота, потеря давления и т. д.)
- Исследование пространства решений; surrogate-модели

### AI Assistance (planned)

- Вывод намерения constraints/features из действий пользователя
- Автодополнение команд; подсказки по параметрам
- Рекомендации по пространству проектирования; автоматический DOE
- Подсказки по настройке решателя и построению сетки в зависимости от контекста

> Подробный прогресс по элементам смотрите в **[Roadmap](#roadmap)** и **JIRA**.

---

## Roadmap

Планирование и backlog отслеживаются в **JIRA**:  
https://hananiah.atlassian.net/jira/software/c/projects/AL/boards/3

Крупные этапы (могут измениться):

1. **P0 — Modeling Foundations**: стабильный граф features, надежный sketcher, базовые операции моделирования, система транзакций, персистентность.
2. **P1 — Meshing & FEA MVP**: pipeline тетра/гекса-сетки; линейная статика/модальный анализ; базовый постпроцессинг.
3. **P2 — CFD MVP**: интеграция сетки и решателя для несжимаемых потоков; поля давления/скорости/температуры; постпроцессинг.
4. **P3 — Optimization**: топологическая оптимизация SIMP; замкнутый цикл обновления параметров; обработка ограничений.
5. **P4 — AI Copilot v1**: вывод ограничений, подсказки по командам, solver presets; обучение на истории проектов.

Подробные проектные документы находятся в **Confluence** (требуется доступ). Публичная часть размещается в **GitHub Wiki**.

---

## Build & Run

В репозитории есть **скрипты сборки в один клик**, которые создают дерево сборки в `../SolidDesigner_Build/`.

### Prerequisites (current)

- **CMake ≥ 3.31**  
  - Windows: репозиторий включает CMake в `ToolChain/cmake` (используется `AutoGenerateVsProject.bat`)  
  - Linux: установите свежую системную версию CMake (или используйте собственную toolchain)
- **C++17 toolchain**: MSVC v143 / GCC 11+ / Clang 15+
- **Qt 5.15.x** с модулями: Core, Gui, Widgets, Network, Quick, Qml
- **OpenCascade (OCCT) SDK** для backend’а OCCT Viewer (см. layout SDK ниже)

### Windows (Visual Studio 2022, x64)

1. Клонируйте с подмодулями:

```bash
git clone --recurse-submodules https://github.com/hananiahhsu/SolidDesigner.git
cd SolidDesigner
```

2. Запустите:

- `AutoGenerateVsProject.bat` (создает `../SolidDesigner_Build/SolidDesigner.sln` и открывает Visual Studio)

3. Соберите конфигурацию `Release|x64` в Visual Studio, затем запустите `SolidDesigner`.

### Linux (Makefiles)

Запустите:

```bash
./SolidDesignerForLinux.sh
```

Этот скрипт выполняет конфигурацию и сборку с использованием `Unix Makefiles` и пишет результаты в `../SolidDesigner_Build/`.

> Примечание: сейчас скрипт передает `-DCMAKE_GENERATOR_PLATFORM=x64`, что является опцией Visual Studio и может игнорироваться Linux-toolchain’ами. Если возникнут проблемы, запустите CMake вручную (следующий раздел).

### Manual CMake (recommended when customizing toolchains)

```bash
cmake -S . -B ../SolidDesigner_Build -G "Ninja" -DCMAKE_BUILD_TYPE=Release
cmake --build ../SolidDesigner_Build --parallel
```

### Third‑party SDK layout (OCCT)

Backend OCCT Viewer ожидает, что SDK OpenCascade экспортирован в:

```
Externals/3rdParty/sdk/<platform>/<Debug|Release>/occt
```

Значения `<platform>` по умолчанию (могут быть переопределены):

- Windows: `msvc2022-x64-md`
- Linux: `linux-x64`

Переопределить из CMake можно так:

- `-DSD_3P_PLATFORM=...`
- `-DSD_3P_CFG=Debug|Release`
- либо напрямую указать `-DOpenCASCADE_DIR=...` на папку, содержащую `OpenCASCADEConfig.cmake`.

### Qt

UI-таргеты сейчас используют **Qt 5** (например, `Qt5::Core`, `Qt5::Widgets`, `Qt5::Quick/Qml` в CMake).  
В Windows некоторые модули задают стандартный `CMAKE_PREFIX_PATH` для `Qt5.15.x`; при необходимости скорректируйте его под вашу локальную установку Qt.

---

## Dependencies

Проект модульный: часть библиотек **вендорится внутри дерева**, а часть ожидается как **внешние SDK**.

### Open-source Stack & Licenses

| Библиотека | Назначение | Где используется | Лицензия (upstream) |
|---|---|---|---|
| **OpenCascade (OCCT)** | B‑Rep kernel + backend OCCT Viewer | `Alice/Core/Runtime/AliceRenderBackendOCCViewer` | LGPL‑2.1 with OCCT exception (upstream) |
| **Qt 5 (Widgets/Quick/Qml)** | Desktop UI (ribbon, панели, диалоги) | `Designer/UI/*`, `Alice/UI/QFrameWork/*` | GPL/LGPL/commercial (Qt) |
| **spdlog** | backend логирования | `Alice/Core/Foundation/AliceBasicTool/*SpdLog*` | MIT |
| **fmt** | форматирование строк | `Alice/Core/Foundation/AliceBasicTool/*Fmt*` | MIT |
| **Open Sans** | шрифтовые ресурсы UI для ribbon | `Alice/UI/QFrameWork/AliceRibbon/OpenSans` | Apache‑2.0 |
| | | | |
| | | | |

> **Примечание по лицензии**: SolidDesigner распространяется под **GPLv3**, но некоторые встроенные/обязательные зависимости имеют лицензии LGPL/MIT/Apache. При распространении бинарных сборок необходимо соблюдать требования соответствующих upstream-лицензий (обязательства по динамической линковке, уведомления, доступность исходников и т. д.).

### Optional / planned adapters (not required for a minimal build)

- Backend’ы рендеринга **OGRE / OSG / VTK / Skylark** существуют как платформенные модули (`Alice/Core/Runtime/AliceRenderBackend*`), но могут требовать дополнительные SDK и пока продолжают развиваться.
- **Meshing / solvers** (FEA/CFD/оптимизация) находятся в активной фазе проектирования; адаптеры будут вводиться постепенно.

---

## Getting Started

Типовой целевой workflow:

1. **Создайте проект** и задайте единицы/допуски по умолчанию.
2. Выполните **эскизирование** на плоскости; используйте ограничения/размеры.
3. Создайте features: **Extrude**, **Revolve**, **Fillet**, **Shell**, **Pattern**…
4. **Соберите** детали; добавьте mates/constraints.
5. **Постройте сетку** модели (глобальные + локальные настройки).
6. Определите **материалы** и **граничные условия**.
7. Запустите **FEA/CFD**; проанализируйте напряжения/деформации, моды и поля течения.
8. **Управляйте параметрами** по результатам (например, уменьшайте толщину, пока напряжение ≤ целевого значения).
9. Сохраните как **проект** и экспортируйте в **STEP/IGES** или форматы сетки.

---

## Plugin & Scripting

- **Plugin ABI**: чистые C++ интерфейсы для геометрических операций, построения сеток, решателей, импортёров/экспортёров и UI add-in’ов.
- **Isolation**: стабильная модель владения и безопасность между DLL (foundation предоставляет утилиты указателей Owning/Weak/Guard).
- **Scripting (planned)**: Python API для автоматизации моделирования, настройки исследований, постобработки результатов и оркестрации циклов проектирования.
- **AI hooks (planned)**: регистрация пользовательских design-advisor’ов и ML-моделей для предсказания намерений и оптимизации.

---

## Data & File Formats

### Native project format (in progress)

Нативный формат задуман как:

- **Structured**: метаданные + типизированные payload’ы (геометрия, сетка, результаты, thumbnails и т. д.)
- **Versioned**: версионирование схемы с явным pipeline обновления
- **Incremental-friendly**: рассчитан на частичную перезагрузку и будущие cloud/workspace-сценарии
- **Stable-identity aware**: ID объектов сохраняются через save/load, copy/paste и обновления

> После стабилизации формата публичная wiki будет содержать каноническую спецификацию.

### Interoperability (planned / incremental)

- **CAD Interop**: импорт/экспорт STEP/IGES (другие форматы через адаптеры)
- **Mesh/Results**: стандартные форматы сеток/результатов для внешних решателей и постобработки (VTK, MED и т. д., планируется)
- **Units**: согласованная система единиц с явными метаданными; размерные параметры в выражениях

---

## Diagnostics, Logging & QA

- Единый **DiagnosticsEngine** с уровнями важности, позициями в исходниках и подключаемыми sinks (консоль, файл, UI-панель).
- Опциональный backend **spdlog** для быстрого thread-aware логирования.
- **Assertions** и **защитные проверки** через границы DLL.
- **Testing** через CTest; fixtures для геометрии, сеток и корректности решателей; воспроизводимые случаи привязываются к JIRA.

---

## Contributing

Контрибьюции приветствуются.

- Изучите JIRA epics/tasks и GitHub Wiki для понимания контекста.
- Обсуждайте крупные предложения до открытия PR.
- Следуйте стилю кода проекта (файл clang-format планируется) и добавляйте unit-тесты.
- Держите коммиты небольшими и хорошо описанными; по возможности связывайте их с тикетами JIRA.

Подходящие первые вклады:

- Исправить проблемы сборки на конкретной платформе/компиляторе
- Добавить фокусные тесты (геометрия, персистентность, решение ограничений)
- Добавить документацию: design notes, диаграммы или минимальные разделы «how it works»

> Документы для контрибьюторов на уровне репозитория (планируются): `CONTRIBUTING.md`, `CODE_OF_CONDUCT.md`.

---

## License

Этот репозиторий лицензирован по **GNU GPL v3.0**. Полный текст см. в `LICENSE`.

> Примечание: сторонние библиотеки могут иметь собственные лицензии; при распространении бинарных сборок необходимо соблюдать их требования.

---

## Acknowledgments

Этот проект стоит на плечах гигантов: OpenCascade, Eigen, fmt, spdlog, Qt и более широкого open-source сообщества.  
Особая благодарность контрибьюторам и исследователям в области CAD/CAE/CFD/оптимизации.

---

## FAQ

**Есть ли API для скриптинга?**  
Python API планируется. Уже существует ранняя внутренняя заготовка; публичный API появится позже.

**Какой стек решателей используется?**  
Внутренние решатели находятся на стадии прототипирования. Также планируются адаптеры к внешним решателям (например, mesh/post).

**Потребуют ли ИИ-функции доступ в интернет?**  
Нет. Цель — поддержка офлайн-инференса на локальных моделях с опциональными cloud-интеграциями.

**Где отслеживать прогресс?**  
В JIRA (roadmap/backlog) и публичной GitHub Wiki. Подробные проектные документы находятся в Confluence (требуется доступ).
