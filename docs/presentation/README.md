# Document Template Library: Presentations

Copyright (C) 2022-2024 Timon Burkard, <timon.burkard@gibz.ch>

This is the LaTeX presentation template library. Use this library as a git submodule in your repo to start writing presentations for your HFIE module.

Note, to also write A4 documents you'll need the document library as well, see [here](https://gitlab.com/GIBZ/teachers/tburkard/documents/document-lib).

## Folder Structure

Your repo should follow this structure:

```
├── documents                    --> Please refer to document-lib
│
└── presentations
    │
    ├── lib/                     --> git submodule presentation-lib
    │   ├── *.tex                --> general tex files for all presentations
    │   └── includes/            --> general include files for all presentations
    │
    ├── presentation1/           --> folder name for a specific presentation
    │   ├── document.tex         --> main tex file of the presentation: see templates
    │   ├── references.bib       --> bibliography of the presentation
    │   └── */                   --> subdirectories for includes of the presentation
    │
    ├── presentation2/           --> folder name for another presentation
    │   └── ...
    │
    └── ...                      --> more presentations...
```

## Create New Presentation

To create presentations for a module, create a new repo and link the presentation lib submodule as `presentations/lib/`.

Refer to https://gitlab.com/GIBZ/teachers/tburkard/documents/templates as an example project to get a starting point for the main tex file (`document.tex`).

## Document Structure

The `document.tex` is structured as follows:

```tex
\documentclass[aspectration=169]{beamer}

\input{settings.tex}

% Variables

\begin{document}

\input{titleframe.tex}

%%%%%%%%%%%%%%%%%%%%%% CONTENT START %%%%%%%%%%%%%%%%%%%%%%

\input{tocframe.tex}

\quote{\vSW}{Code is like humor. When you have to explain it, it's bad.}{Cory House}

\goals%
{
    \item wissen\dots
    \item verstehen\dots
    \item können\dots
}

%%%%%%%%%%%%%%%%%%%%%% CONTENT END %%%%%%%%%%%%%%%%%%%%%%

\miniframesoff

\questions{}

\input{refframe.tex}

\end{document}
```

### Variables

The variables can be used to change different behaviors of the document.

Here is a description of the variables:

| Variable     | Description        | Example                                                       |
| ------------ | ------------------ | ------------------------------------------------------------- |
| `\title`     | Presentation title | SW01: Beispiel-Präsentation                                   |
| `\author`    | Author name        | Timon Burkard                                                 |
| `\institute` | Institution        | HFIE -- Höhere Fachschule für Informatik und Elektronik       |
| `\date`      | Date (semester)    | HS22                                                          |
| `\vSW`       | Semester week      | SW01                                                          |
| `\vEmail`    | Author email       | timon.burkard@gibz.ch                                         |
| `\vModule`   | Module name        | BM\_ED3 -- RT-Betriebssysteme \& Parallele Programmausführung |

### Content

Except the variables, all changes and insertions must only be added within the following section of `document.tex`:

```tex
%%%%%%%%%%%%%%%%%%%%%% CONTENT START %%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%% CONTENT END %%%%%%%%%%%%%%%%%%%%%%
```

## Build The Document

To build the document you'll need:
 - `pdflatex`
 - `bibtex`

 You can build the document in your favorite Tex-Editor or use `make`.

 ### Make

 The following make commands are supported, see [Makefile](https://gitlab.com/hfie-ed/documents/templates/-/blob/main/presentations/template/Makefile):

| Command           | Description                                                                       |
| ----------------- | --------------------------------------------------------------------------------- |
| `make`            | Generate PDF file (document.pdf)                                                  |
| `make bib`        | Create bibliography (uses `bibtex`) (included in `make`)                          |
| `make diagrams`   | Convert `diagrams/*.drawio` &rarr; `diagrams/*.pdf` files (included in `make`)    |
| `make animations` | Convert `animations/*.gif` &rarr; `animations/*-X.png` files (included in `make`) |
| `clean temps`     | Clean temp files (included in `make`)                                             |
| `clean`           | Clean all files (temps + PDFs)                                                    |

Note, `make` may output some errors if bibliography is not used. Nevertheless, the PDF should be generated correctly.

### draw.io diagrams

You can use [draw.io](https://app.diagrams.net/) diagrams. Put them in the `diagrams/` subdirectory.

`make` will automatically convert your `.drawio` files into `.pdf` files, which can be used in the template as figures. Please refer to the example in the template.

To do so, [draw.io Desktop](https://www.diagrams.net/) needs to be installed and added to the PATH environmental variable.

### SVG images

You can insert `SVG` images. Put them in the `graphics/` subdirectory.

`make` will automatically convert your `.svg` files into `.pdf` files, which can be used in the template as figures. Please refer to the example in the template.

To do so, [inkscape](https://inkscape.org/) needs to be installed and added to the PATH environmental variable.

### GIF animations

You can insert `GIF` animations. Put them in the `animations/` subdirectory.

`make` will automatically convert your `.gif` files into multiple `.png` files, which can be used in the template as animations. Please refer to the example in the template.

To do so, [ImageMagick](https://imagemagick.org/) needs to be installed and added to the PATH environmental variable.
