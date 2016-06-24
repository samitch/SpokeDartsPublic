# SpokeDarts
SpokeDarts sphere-packing sampling in any dimension. Advancing front sampling from radial lines (spokes) through prior samples.

1. Copyright and Citations
2. Compiling
3. Interface


1. 
Copyright 2016 Sandia Corporation. Under the terms of Contract DE-AC04-94AL85000 with Sandia Corporation, the U.S. Government retains certain rights in this software.
SCR#:2084.0

To credit this work, please cite the following paper:

@article{spokedarts_journal,
author = {Scott A. Mitchell and Mohamed S. Ebeida and Muhammad A. Awad and Chonhyon Park and Anjul Patney and Laura P. Swiler and Dinesh Manocha and Li-Yi Wei and Ahmad A. Rushdi},
title = {Efficient Blue Noise Sampling in any Dimension},
journal = {submitted to ACM Trans. Graph.},
volume = {},
number = {},
month = {},
year = {2016},
issn = {},
pages = {},
articleno = {},
numpages = {},
url = {},
doi = {},
acmid = {},
publisher = {ACM},
address = {New York, NY, USA},
keywords = {Sampling; Algorithms, Theory, Experimentation; line sampling, high dimension, step blue noise, Delaunay graph, global optimization, motion planning},
note={Open source software available from \url{https://github.com/samitch/SpokeDartsPublic}  An earlier version of this paper appears as \url{http://arxiv.org/abs/1408.1118}}
}

% use the  "archivePrefix", "eprint", and "primaryClass" fields if your bibliography style handles it,
% otherwise usepackage{url} in the latex file and use the "note" field in the bib file entry
% see also http://arxiv.org/hypertex/bibstyles/
@Article{spokedarts_arxiv,
author = {Mohamed S. Ebeida and Scott A. Mitchell and Muhammad A. Awad and Chonhyon Park and Laura P. Swiler and Dinesh Manocha and Li-Yi Wei},
title = {Spoke Darts for Efficient High Dimensional Blue Noise Sampling}
journal   = "pre-print",
volume    = "",
year      = "2014",
pages     = "12",

eprinttype={arxiv},
archivePrefix = "arXiv",
eprint        = "1408.1118",
primaryClass  = "cs.GR",
version = {1},
date={2014-8-5},
note = {arXiv:1408.1118 [cs.GR] \url{http://arxiv.org/abs/1408.1118}},
_note={arxiv submission 1038046},
}
% date = 5 aug 2014

This code:


2. Compiling
The software has been compiled using Xcode on Mac OS X, and on Unix. The code used c++11 extensions.
If you want to compile it multithreaded, you should consider disabling the use of the Mem_Pool memory managed pool of objects.

3. Interface
There is no interface developed currently. For examples of how to run the various sampling algorithms and their options, see main.cpp
