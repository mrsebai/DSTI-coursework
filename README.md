# DSTI-coursework
This repo contains all course assignments, exams, and projects produced during the year of study at [Data ScienceTech Institute](https://www.datasciencetech.institute).

## C-Programming Unit

We were assigned a fun little project: coding a *Small Formal Computation Engine Using Reverse Polish Notation Implementation*.
The goal is to acquire from the user a *mathematical expression in [infixed notation](https://en.wikipedia.org/wiki/Infix_notation)* and turn it into an *expression in postfixed notation* (also known as [Reversed Polish Notation](https://en.wikipedia.org/wiki/Reverse_Polish_notation)). The conversion from infixed to postfixed notation is implemented using [The famous Shunting-yard algorithm](https://en.wikipedia.org/wiki/Shunting-yard_algorithm).

Our implementation is in Plain C using a linked-list data structure and has the following features:
- power `^` operator support along with `+`, `-`, `*`, `/`, `(` and `)` operators
- support for multi-letter variable and their repetition
- negative sign full support without collision with a subtraction operator

Some examples:
- input in infixed notation:`3 + 4 × 2 ÷ ( 1 − 5 ) ^ 2 ^ 3`
- the output of the same expression in Reversed Polish Notation (or postfixed notation): `3 4 2 × 1 5 − 2 3 ^ ^ ÷ +`
- input with abstract variable names with repetition: `-a +2 *a +5*(alpha - beta +b *c +a)/alpha -(-beta)^c`

### Implementation:

- [Link to c file ](C-Programming-Unit/maher_formal_engine.c)
- [Link to log file](C-Programming-Unit/MaherFormalEngine.log.txt)

## SQL Unit
Using [WideWorldImporters Sample Database for SQL Server](https://github.com/microsoft/sql-server-samples/tree/master/samples/databases/wide-world-importers), the 5 hours exam consists of 5 queries intended to produce table results that should perfectly match the provided ones.
- [Question & solution 1](SQL-Unit/SQL-Answer-1.txt)
- [Question & solution 2](SQL-Unit/SQL-Answer-2.txt)
- [Question & solution 3](SQL-Unit/SQL-Answer-3.txt)
- [Question & solution 4](SQL-Unit/SQL-Answer-4.txt)
- [Question & solution 5](SQL-Unit/SQL-Answer-5.txt)

## Foundation and Advanced Statistics for Machine Learning Unit
Two intensive learning units focusing on classical statistical modeling methods. The foundation part concentrates on discrete and continuous probability distribution, density functions, univariate linear regression and hypothesis testing.
- [Link to Fondation Statistics Exam](Fsml%20Maher%20SEBAI.pdf)

The Advanced part of the learning module addresses advanced statistical methods including multivariate linear models, Analysis of Variance, Model Regularization methods (Lasso & Ridge), Model selection methods, Decision trees, bagging and boosting, Random Forests, Dimensionality reduction using Principal Component Analysis.
- [Link to Advanced Statistics Exam](ASML-EXAM-Maher-SEBAI.pdf)

## Survival Analysis Unit
The produced report, written in `R`, attempts to analyze two Birth spacing datasets in the context of Event History Analysis, a field that borrows a lot of the Clinical [Survival Analysis](https://en.wikipedia.org/wiki/Survival_analysis) techniques to study sociological and historical phenomena. Both datasets are provided by the Medical Birth Registry of Norway. The first dataset describes the first to second birth spacing. The second dataset, in the same spirit, describes the second to third birth spacing. The two dataset does not share exactly the same covariates. We will try to study and highlight what factor is influential for the observed birth spacing. 

In the first section, we will import, clean the two datasets and introduce the embedded covariates. In the second section, we perform some exploratory analysis that will guide us in the remaining report using [Kaplan–Meier estimator](https://en.wikipedia.org/wiki/Kaplan%E2%80%93Meier_estimator). In the third section [logrank test](https://en.wikipedia.org/wiki/Logrank_test) for groups will help us discover the first influential categorical factors. the next section, [Cox Proportional hazard modeling](https://en.wikipedia.org/wiki/Proportional_hazards_model) will help us select the significant covariate and quantify their effect size. The conclusion will be the occasion to list our findings.
- [Link to the R report](Maher-SEBAI-Birth_Spacing-Report.pdf)

## Metaheuristic Optimization Unit
A learning module focusing on [Metaheuristic Optimization](http://www.scholarpedia.org/article/Metaheuristic_Optimization) Algorithms. Studied Algos include: Simulated Annealing, Genetic Algorithm, Ant Colony Optimization, Particle Swarm, etc ...
In the report, given the Paris Metro Map, we solved a [Travel Salesman Problem](https://en.wikipedia.org/wiki/Travelling_salesman_problem) Variation by expressing it as [Hamiltonian Path](https://en.wikipedia.org/wiki/Hamiltonian_path) finding problem. The slides expose our approach, the `R` packages used and the obtained results.

- [Link to the R report](Maher-SEBAI-MetaH-report.pdf)

## Semantic Web Unit
[Semantic Web](https://en.wikipedia.org/wiki/Semantic_Web) learning unit is all about the data formats and the technologies to enable it like [RDF](https://en.wikipedia.org/wiki/Resource_Description_Framework), [N-3](https://en.wikipedia.org/wiki/Notation3), [Turtle](https://en.wikipedia.org/wiki/Turtle_(syntax)), How to query these data using [SPARQL](https://en.wikipedia.org/wiki/SPARQL), and how to expand the vocabulary using [OWL](https://en.wikipedia.org/wiki/Web_Ontology_Language) ontology.

- [Link to report](000-Maher_SEBAI_handout_DSTI_SemanticWeb.pdf)

## Agent-Based Modeling Unit
A fun project learning multi-agent environment modeling using [Netlogo](https://ccl.northwestern.edu/netlogo/) language.

- [Link to Netlogo project code](langton-ant-Maher_SEBAI.nlogo)

## Intro To Deep Learning Unit
Foundations of modern Deep learning. In the module assignment a [Mask R-CNN](https://arxiv.org/abs/1703.06870#:~:text=The%20method%2C%20called%20Mask%20R,CNN%2C%20running%20at%205%20fps.) [pretrained model](https://github.com/matterport/Mask_RCNN) is used in inference mode. This project set the stage for a more ambitious deep dive in Deep learning modeling for a [semantic segmentation project](https://github.com/mrsebai/aerial-tile-segmentation) using Tensorflow 2.x in my internship at Airbus.

- [Link to report](Mask%20R-CNN%20report%20-%20Maher-SEBAI.pdf)
