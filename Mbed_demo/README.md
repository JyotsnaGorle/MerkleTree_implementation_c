### Generating Merkle Trees and execution of Mrkle Tree Traversals

This application is used to generate a Merkle Tree of a given height. Each tree can be uniquely differentiated by using a unique salt in every execution.
These values can be altered in the respective files.
 - salt: in the file leafs.c, variable : ``salt``.
 - tree height: in the main method, in file, client.c. The first parameter for the method ``init_tree_height_leaves(tree_height, leaf_count)``.

 The implementation is based on the Merkle Tree generation algorithm proposed in this [paper](), along with the [Tree traversal algorithm] that runs with a ``Log (N)`` space
 and time complexity.

 Currently the application is configured to generate a Merkle Tree of height 21.

## Software and Hardware requirements
	* This project runs on any advanced computers or laptops.
	* You may need Visual Studio to run the project application.

## Open this project
	* double click the Mbed_demo.sln file to open the project solution in Visual Studio.

## Build and Run the application
	* In order to build the project press ``ctr + shift + b``
	* To run the built binary, use ``Fn5`` in a windows machine.

## Sample output
	The application logs every leaf and intermediate node generated. The final output includes only the path of the left most leaf node of the tree to its root, along with
	its authentication respective path.

	```
	Time elapsed: 3205.000000
	STACKS:
	0 a6, 3f, 98, 1f, 1d, 24, 32, 50, c9, 5f, 76, 61, 99, ee, 63, c5, 6b, 3b, fd, 47, 2, a1, d9, d, 91, 3b, 89, 45, c0, 6e, c9, 98,
	1 78, a2, cb, 87, c0, f5, 33, ff, db, ce, 5a, b8, 3d, f6, 53, cb, dc, b, 1a, 15, be, 9c, d9, ec, 92, b4, b0, 75, 8d, ac, 86, 82,
	2 a, 2, 5e, 20, 4f, ec, 86, 59, 72, 60, cd, 1c, 4, cd, 2f, 50, 71, 13, e4, fe, 9d, 1f, 1b, 6a, 6d, 85, c8, 3a, 81, b, fd, 9f,
	3 e0, 2b, 69, 1a, be, ab, 1f, be, 27, 29, 7c, bc, d6, 8f, 6c, 7e, f3, a1, 68, 4b, 89, fd, e, a7, d4, 54, e6, cc, a6, 1b, e4, c5,
	4 4f, 2d, 6e, 7c, 65, b5, 49, 18, 60, 16, aa, 3d, f, 87, 81, 18, 8b, 47, 9, 13, 13, 72, ee, c8, 22, 3d, e5, d, 45, 81, 26, db,
	5 3c, 7a, ea, 74, df, 2f, c4, bf, 40, 13, d4, f0, b4, 4a, 27, f2, 15, 5d, a8, cd, 40, ed, a1, c3, e1, 46, 4c, b4, 36, 74, 82, 18,
	6 9e, 82, 99, f5, 22, 93, 82, d3, 11, f2, 7c, 7a, 30, 63, c, aa, 9b, 57, 20, 9, 59, 45, 8c, c1, 35, 42, 47, af, 8b, 27, 3d, 79,
	7 d5, e3, 4d, 5d, 80, db, 4a, 2d, 33, b6, 6, 8b, ab, e7, 6, 3d, 5a, ba, 30, bf, 15, 9c, 52, d8, e0, 60, 32, 65, 4d, 36, 83, b8,
	8 45, 25, 57, 16, 43, 14, 80, a8, a, 26, d9, 57, 1a, a8, 18, 98, 35, 2a, 32, d3, 5b, 38, e9, b6, df, 90, c, b, 7f, 87, 2c, db,
	9 fb, 8d, ab, 42, c0, 4f, b3, e1, 14, 92, 97, c5, 83, d2, dd, 52, ff, ba, 6f, 3d, d2, 37, 5c, c7, 2, af, fd, 20, 2c, d5, 9, 4a,
	10 9c, e2, 9c, f8, 48, 47, 78, 36, 63, 48, 24, 66, 61, 35, ca, 0, 3c, d1, ec, 8d, 6f, ff, 2f, 33, a2, 77, 72, 88, ea, 51, b6, 94,
	11 89, f7, cf, 9b, 75, 38, a0, b6, 6a, 8a, 4, 9, 37, 37, 39, 5c, d2, ec, ec, 6, e1, 45, 68, 7a, b3, 98, 37, 29, f0, 6e, 0, 8,
	12 72, d2, ca, 3a, d1, 5a, d7, a6, 2d, ee, 47, b1, 58, 19, c8, 26, 87, e5, 7e, 10, ef, 62, 12, a, 72, 54, 7d, 5c, 2c, ff, 45, 32,
	13 1a, 8e, 24, ce, 62, 5d, 58, a3, 9a, ab, 1, e1, 9e, e1, 17, c8, 64, 2f, 89, 3c, c1, 58, ac, 5c, 1e, e, c1, 36, 48, cc, 67, e1,
	14 9e, 1d, e2, c, ee, c9, 2f, 91, fa, 81, c8, 9c, 17, 99, ef, c3, 10, 4a, 26, c9, b, d2, 8a, 27, 96, 53, b4, 64, d1, 41, 6c, 25,
	15 65, 2, da, 1b, 57, 2, d6, 14, 5d, 77, 41, cf, c4, f7, 5a, f2, fe, fd, 2b, b, f1, fc, 97, 69, a6, ec, 3e, 4e, ba, de, b8, 69,
	16 c0, b0, 7c, fb, 84, 56, cb, 61, b9, 8a, 9c, b2, 4a, d, 28, ca, 63, ff, f3, 56, a4, 6c, 5, 45, b7, 57, 92, b4, d5, 83, 94, 2e,
	17 a7, 38, 3c, 6c, ea, 43, 2f, d7, e0, bd, 8, a7, 8c, dd, c4, 75, 23, bf, 1f, 1, 4, 33, b2, e6, bd, 46, 17, 44, ea, f4, 4a, 30,
	18 78, 2d, 28, 27, a6, ae, ed, 2d, 90, 75, ad, e, b7, 35, 81, cc, fe, c9, bb, 75, 8f, be, c4, ad, 79, 4, d1, e2, 55, bb, cc, e2,
	19 da, 94, e9, 9c, 48, cd, 89, f8, 4b, 4f, d1, e2, 76, 2c, 14, 65, ae, 68, 9a, 9f, 32, 50, 33, 2, 37, 85, 1b, a6, 63, 49, 7, d3,
	20 6f, 11, e1, 5d, de, d5, ae, 9a, 6d, 2c, ec, 67, b4, 4e, f7, 12, 42, 7d, 56, aa, 48, 36, b9, d9, b1, f7, d8, f1, 5e, 6e, a8, fe,
	AUTH:
	0 92, 6b, bd, d2, 3a, b6, b9, 7, 2f, 21, da, ec, 3e, e8, db, 71, 3c, bf, 4f, 4, f, c2, 22, 76, ff, 52, 50, aa, 9, 9a, ab, 9c,
	1 b5, c9, f5, be, 9d, e7, f0, d3, 52, 18, 3c, 1d, 1c, a2, 13, 56, 8c, e8, a7, be, c5, 89, 88, a0, 26, a0, 9b, 7f, 59, c3, 47, d4,
	2 6f, 4f, 7c, 14, d3, 75, cc, a1, 7b, 2a, 4c, 9f, b5, da, a, 13, 95, 67, f7, a9, 74, 77, 5e, bb, 8f, 43, ab, 2b, 91, 17, 4e, a5,
	3 5c, 15, 6e, d8, ec, 6e, 74, 2, 3f, 9, e0, fe, 24, 48, 44, 7a, ef, 3e, c2, 57, 52, b8, 5d, a, 87, e7, e4, bf, 38, f2, 37, 31,
	4 d6, cd, ce, c6, a8, a5, bb, d7, 67, a4, 4f, e0, 95, 6, 4a, 46, 53, 7b, d4, af, bc, 2f, 68, a3, c3, 8a, 81, f1, db, a6, 29, 5f,
	5 88, 34, c1, 90, cf, 9f, 56, 28, 34, 69, 7b, 8a, fe, 70, c, 46, 29, 8c, 52, 2, a3, 8a, da, cc, 9b, c8, 55, 7, 1d, a0, 1f, 7b,
	6 bc, 59, 40, 70, e1, e6, cf, 48, f4, 24, a2, c5, a6, 6a, d9, c, 43, 4d, 57, 32, 1c, d5, 82, ab, 6d, 5d, 68, c6, ab, d8, 88, 6e,
	7 94, b1, 96, 88, 58, 36, ad, 40, b7, fb, e7, a0, b8, 86, 4c, 55, 44, 6b, b5, 1, f6, 10, 49, 49, 51, 76, 13, 13, eb, e6, 99, b1,
	8 f6, 19, e5, 1b, 29, 5c, ed, ba, e1, 7b, ed, 52, d, ba, c8, f7, 23, 2d, 3e, 2e, c7, 5f, 58, 8d, e4, 9d, 1f, 3a, b3, b8, 1f, 18,
	9 78, bc, 3f, f0, c6, 10, ea, 49, 73, c5, e0, ab, 6, 26, fc, 81, a8, a3, cd, 35, a5, f8, 91, 5c, b6, 2, d9, 64, ed, dd, 68, 95,
	10 37, 2d, 69, a, 51, eb, d5, d2, 1, b8, ac, 60, 56, 5a, 43, e5, 55, b2, d1, d7, c4, fb, 82, ed, c, 9, 7b, 74, f5, a3, de, 47,
	11 d, 62, e7, 46, ef, 57, e4, 3, bb, cc, 50, 6c, 8d, 47, b4, 94, 27, df, de, 43, 88, b8, 93, 92, fd, ee, bf, fb, 26, bb, c9, fe,
	12 66, f9, 40, 5b, ae, 46, 4, 7d, 53, dd, b1, d2, 6b, 9b, 36, 7d, e1, 7d, 8c, 56, d1, 74, ec, e1, 8a, 71, 80, 64, 9d, fd, 2e, bd,
	13 53, 96, 1a, a5, 6, 5b, df, ee, b, 64, 72, bf, 0, db, 1d, 69, 38, 7d, e6, 30, 0, 1d, dd, 73, 4a, 25, d3, 2c, 86, 68, e1, c8,
	14 6, be, c5, 54, c4, 98, 3c, c7, 81, a1, d3, 57, 3b, 79, 4f, be, de, 28, da, 2c, fd, 64, 7e, d7, 4f, a1, 1a, 4c, 59, e1, 42, 52,
	15 eb, 97, dd, 34, e0, 4d, 46, ce, 43, 7c, b5, 69, ad, 9a, 1c, 69, e9, 31, c5, 50, 16, cd, 19, dd, c0, 46, a1, 1d, 96, 25, 79, 5f,
	16 d0, ea, db, bb, ce, 9c, 4e, 59, 6e, 7e, af, af, 74, 3e, 4e, 2b, a5, 11, 1, 36, e2, 92, 7c, f6, 62, 9c, 27, cd, ad, eb, 7d, 77,
	17 0, e9, 3, a9, 9a, 65, bb, f8, ea, cb, 34, ae, a2, 11, 13, 38, 69, 2b, c1, 45, f5, 3d, 72, 58, 2d, ce, 49, 84, 61, 61, d0, 31,
	18 ef, b7, b7, e4, 4, 8b, 90, c0, bc, f8, 43, 9a, 35, 43, 88, a4, c9, 6a, 17, 78, e4, fa, 77, a4, f9, 9b, 69, be, d, b4, 12, 35,
	19 11, f5, cd, 38, 92, 45, 83, 19, 41, 48, c0, 7, e1, f9, 62, 4f, c0, d2, dd, 72, 72, 2e, 58, 9a, 26, bf, 60, 0, b, 27, 1b, ae,

	```