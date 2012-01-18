/*
	MilkshapeModel.h

		Loads and renders a Milkshape3D model. 

	Author:	Brett Porter
	Email: brettporter@yahoo.com
	Website: http://rsn.gamedev.net
	Copyright (C)2001, Brett Porter. All Rights Reserved.

	This file may be used only as long as this copyright notice remains intact.
*/

#ifndef MILKSHAPEMODEL_H
#define MILKSHAPEMODEL_H

#include "Model.h"

struct BoundingBox {

	float xmin, ymin, zmin;
	float xmax, ymax, zmax;

};

class MilkshapeModel : public Model
{
	public:
		/*	Constructor. */
		MilkshapeModel();

		/*	Destructor. */
		virtual ~MilkshapeModel();

		/*	
			Load the model data into the private variables. 
				filename			Model filename
		*/
		virtual bool loadModelData( const char *filename );

		void updateTransfMatrix();
		void drawBoundingBox();
		BoundingBox getTBbox() { return t_bbox; };

	private:
		BoundingBox bbox;	
		BoundingBox t_bbox;

};

#endif // ndef MILKSHAPEMODEL_H
