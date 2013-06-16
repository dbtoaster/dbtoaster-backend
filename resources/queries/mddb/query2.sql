INCLUDE 'resources/queries/mddb/schemas.sql';

select P1.trj_id, P1.t,
	 dihedral_angle(P1.x,P1.y,P1.z,
					P2.x,P2.y,P2.z,
					P3.x,P3.y,P3.z,
					P4.x,P4.y,P4.z)
	 as phi_psi,
	 DM.dim_id
from Dihedrals D,         Dimensions DM,
   AtomPositions P1,    AtomPositions P2,    AtomPositions P3,    AtomPositions P4,
   AtomMeta M1,         AtomMeta M2,         AtomMeta M3,         AtomMeta M4
where P1.t = P2.t           and P1.t = P3.t           and P1.t = P4.t
and   P1.trj_id = P2.trj_id and P1.trj_id = P3.trj_id and P1.trj_id = P4.trj_id
and   (D.atom_id1 = M1.atom_id and M1.atom_id = P1.atom_id)
and   (D.atom_id2 = M2.atom_id and M2.atom_id = P2.atom_id)
and   (D.atom_id3 = M3.atom_id and M3.atom_id = P3.atom_id)
and   (D.atom_id4 = M4.atom_id and M4.atom_id = P4.atom_id)
and   (D.atom_id1 = DM.atom_id1 and D.atom_id2 = DM.atom_id2 and
	 D.atom_id3 = DM.atom_id3 and D.atom_id4 = DM.atom_id4)
and (   (M1.atom_name = 'N'  and M2.atom_name = 'CA' and M3.atom_name = 'C')
   or (M2.atom_name = 'N'  and M3.atom_name = 'CA' and M4.atom_name = 'C') )
;
