INCLUDE 'resources/queries/mddb/schemas.sql';

select P.trj_id, P.t, avg(vec_length(P.x-P2.x, P.y-P2.y, P.z-P2.z)) as rdf
from AtomPositions P, AtomMeta M,
     AtomPositions P2, AtomMeta M2
where P.trj_id        = P2.trj_id 
and   P.t             = P2.t
and   P.atom_id       = M.atom_id
and   P2.atom_id      = M2.atom_id
and   M.residue_name  = 'LYS'
and   M.atom_name     = 'NZ'
and   M2.residue_name = 'TIP3'
and   M2.atom_name    = 'OH2'
group by P.trj_id, P.t;
