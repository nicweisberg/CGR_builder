# CGR_builder
Takes in sequences of letters and builds chaos game representations in .pbm format

Chaos game representations are a method for creating a visual pattern from a one dimesional sequence. CGRs are popular in bioinformatics as they provide a useful way of representing long sequences of DNA. Since every unique sequence produces a unique CGR, these patterns can be used to identify correlations between certain genomes and certain physical characteristics or ailments. The method I used to produce these CGRs is as follows:

1) Have each corner of the canvas represent a nucleotide (A, C, T, G)
2) Start with a dot halfway between the middle of the canvas and the corner representing the first character in the sequence
3) For every remaining character in the sequence, place a dot halfway between the previous dot and the corresponding corner

This project allowed me to develop my skills coding in C, using pointer arithmetic, allowocation of memory for arrays, using makefiles and source modules, manipulating .PMB files, and building test drivers.
