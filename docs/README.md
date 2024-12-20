# LaTeX-Template

This is a LaTeX document template.

## Folder Structure

The folder follows this structure:

```
root
├── documentation.tex  --> Main TEX file
│
├── references.bib    ---> Bibliography
│
├── coverpage.tex      --> TEX file for cover page
├── titlepage.tex      --> TEX file for title page
│
├── acronympage.tex    --> TEX file for page with list of acronyms (abbreviations)
├── codepage.tex       --> TEX file for page with list of code snippets (listings)
├── equationpage.tex   --> TEX file for page with list of equations (formulas)
├── figurepage.tex     --> TEX file for page with list of figures (images)
├── referencepage.tex  --> TEX file for page with list of references
├── tablepage.tex      --> TEX file for page with list of tables
├── tocpage.tex        --> TEX file for page with TOC (table of contents)
│
├── settings.tex       --> Settings (preamble)
│
├── attachments/*      --> Includes: PDF documents
├── diagrams/*         --> Includes: draw.io diagrams
├── graphics/*         --> Includes: pictures and images
├── sourcecode/*       --> Includes: sourcecode snippets
└── tables/*           --> Includes: CSV tables
```

## Document Structure

The `documentation.tex` is structured as follows:

```tex
\documentclass[11pt,a4paper,hidelinks]{article}

\input{settings.tex}

% Variables

% Acronyms

\begin{document}

\input{coverpage.tex}
\input{titlepage.tex}
\input{tocpage.tex}
\input{acronympage.tex}
\input{figurepage.tex}
\input{equationpage.tex}
\input{tablepage.tex}
\input{codepage.tex}

%%%%%%%%%%%%%%%%%%%%%% CONTENT START %%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%% CONTENT END %%%%%%%%%%%%%%%%%%%%%%

\input{referencepage.tex}

\end{document}
```

### Variables

The variables can be used to change different behaviors of the document.

Here is a description of the variables:

| Variable             | Description               | Example                                                         |
| -------------------- | ------------------------- | --------------------------------------------------------------- |
| `\vTitle`            | Title                     | Radarbasierte Messung von Fliessgeschwindigkeiten               |
| `\vModule`           | Module                    | Bachelor-Thesis                                                 |
| `\vAuthorFirstName`  | First name of the author  | Timon                                                           |
| `\vAuthorLastName`   | Last name of author       | Burkard                                                         |
| `\vAuthorJob`        | Authors job               | Studierender B.Sc.\ Elektrotechnik und Informationstechnologie  |
| `\vUniversity`       | University                | Hochschule Luzern                                               |
| `\vDepartment`       | Department                | Technik \& Architektur                                          |
| `\vDegree`           | Degree                    | Bachelor Elektrotechnik und Informationstechnologie             |
| `\vSemester`         | Semester                  | FS21                                                            |
| `\vProfessor`        | Professor                 | Prof.\ Dr.\ Eberle, Patric                                      |
| `\vExpert`           | Expert                    | Hr.\ Jäggi, Reto                                                |
| `\vCity`             | City                      | Horw                                                            |
| `\vClassification`   | Classification            | Vertraulich                                                     |
| `\vAbstractGerman`   | Abstract in German        | Die vorliegende Bachelor-Thesis befasst sich mit...             |
| `\vAbstractEnglish`  | Abstract in English       | This bachelor thesis deals with...                              |

### Acronyms

If you'd like to use acronyms insert your acronyms as follows:

```tex
\newacronym{ba}{BA}{Beispiel Abkürzung}
```

Note, when a new acronym is added, the following command needs to be run:
```
makeglossaries document
```

If you are using `make` this will be done automatically.

The acronym can then be used as `\acrshort{ba}`, `\acrlong{ba}` and `\acrfull{ba}` in the document.

### Content

Except the variables and acronyms, all changes and insertions must only be added within the following section of `documentation.tex`:

```tex
%%%%%%%%%%%%%%%%%%%%%% CONTENT START %%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%% CONTENT END %%%%%%%%%%%%%%%%%%%%%%
```

## Build The Document

To build the document you'll need:
 - `pdflatex`
 - `bibtex`
 - `makeglossaries`

 You can build the document in your favorite TEX-Editor (e.g., vscode with latexmk plugin) or use `make`.

 ### Make

 The following make commands are supported, see [Makefile](Makefile):

| Command       | Description                                                                            |
| ------------- | -------------------------------------------------------------------------------------- |
| `make`        | Make PDF (document.pdf)<br>clean temp files                                            |
| `clean`       | Clean all files (temps + PDFs)                                                         |
| `clean temps` | Clean temp files                                                                       |

### draw.io diagrams

You can use [draw.io](https://app.diagrams.net/) diagrams. Put them in the `diagrams/` subdirectory.

`make` will automatically convert your `.drawio` files into `.pdf` files, which can be used in the template as figures. Please refer to the example in the template.

To do so, [draw.io Desktop](https://www.diagrams.net/) needs to be installed and added to the PATH environmental variable.

### SVG images

You can insert `SVG` images. Put them in the `graphics/` subdirectory.

`make` will automatically convert your `.svg` files into `.pdf` files, which can be used in the template as figures. Please refer to the example in the template.

To do so, [inkscape](https://inkscape.org/) needs to be installed and added to the PATH environmental variable.
