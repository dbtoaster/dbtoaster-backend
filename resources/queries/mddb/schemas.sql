create stream AtomPositions (
    trj_id  int,
    t       int,
    atom_id int,
    x       float,
    y       float,
    z       float
)   FROM FILE 'examples/data/mddb/atompositions.csv'
  LINE DELIMITED CSV;

create table AtomMeta (
    protein_id   int,
    atom_id      int,
    atom_type    varchar(100),
    atom_name    varchar(100),
    residue_id   int,
    residue_name varchar(100),
    segment_name varchar(100)
)   FROM FILE 'examples/data/mddb/atommeta.csv'
  LINE DELIMITED CSV;

create table Bonds (
    protein_id   int,
    atom_id1     int,
    atom_id2     int,
    bond_const   float,
    bond_length  float
)   FROM FILE 'examples/data/mddb/bonds.csv'
  LINE DELIMITED CSV;

create table Angles (
    protein_id  int,
    atom_id1    int,
    atom_id2    int,
    atom_id3    int,
    angle_const float,
    angle       float
)   FROM FILE 'examples/data/mddb/angles.csv'
  LINE DELIMITED CSV;

create table Dihedrals (
    protein_id  int,
    atom_id1    int,
    atom_id2    int,
    atom_id3    int,
    atom_id4    int,
    force_const float,
    n           float,
    delta       float
)   FROM FILE 'examples/data/mddb/dihedrals.csv'
  LINE DELIMITED CSV;

create table ImproperDihedrals (
    protein_id  int,
    atom_id1    int,
    atom_id2    int,
    atom_id3    int,
    atom_id4    int,
    force_const float,
    delta       float
)   FROM FILE 'examples/data/mddb/improperdihedrals.csv'
  LINE DELIMITED CSV;

create table NonBonded (
    protein_id  int,
    atom_id1    int,
    atom_id2    int,
    atom_ty1    varchar(100),
    atom_ty2    varchar(100),
    rmin        float,
    eps         float,
    acoef       float,
    bcoef       float,
    charge1     float,
    charge2     float
)   FROM FILE 'examples/data/mddb/nonbonded.csv'
  LINE DELIMITED CSV;

create table ConformationPoints (
  trj_id        int,
  t             int,
  point_id      int
) FROM FILE 'examples/data/mddb/conformationpoints.csv'
  LINE DELIMITED CSV;

create table Dimensions (
    atom_id1    int,
    atom_id2    int,
    atom_id3    int,
    atom_id4    int,
    dim_id      int
) FROM FILE 'examples/data/mddb/dimensions.csv'
  LINE DELIMITED CSV;
  

create table Buckets (
  dim_id          int,
  bucket_id       int,
  bucket_start    float,
  bucket_end      float  
) FROM FILE 'examples/data/mddb/buckets.csv'
  LINE DELIMITED CSV;

