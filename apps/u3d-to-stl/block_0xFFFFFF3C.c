//***************************************************************************
//
//  Copyright (c) 1999 - 2006 Intel Corporation
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//
//***************************************************************************
//

#include "u3dparsefile.h"

U3dStatus u3dDisposeInfo0xFFFFFF3C(U3dCallBack *u3dcb, U32 position,
                                   U8* pData, U32 size, U32* readData)
{
	U32         shift = 0;
	U16			stringlen;
	U32			index;
	char		value[65536];

	u3dcb->data = pData;
	u3dcb->size = size;
	u3dDecoderReset(u3dcb->u3ddecoder, u3dcb, myMap);
	if(size < sizeof(U16)) {
		return 0;
	} /* if */
	size -= sizeof(U16);

	printf("\n");

	// Mesh name
	u3dGetU16(u3dcb->u3ddecoder, &stringlen);
	if(size < stringlen) {
		return 0;
	} /* if */
	for(index = 0; index < stringlen; index++) {
		u3dGetU8(u3dcb->u3ddecoder, &value[index]);
	} /* for */
	value[index] = 0;

	printf("MeshName: %s\n", value);

	// Chain Index
	U32 chainIndex, startResolution, endResolution;
	u3dGetU32(u3dcb->u3ddecoder, &chainIndex);
	printf("ChainIndex: %d\n", chainIndex);

	u3dGetU32(u3dcb->u3ddecoder, &startResolution);
	printf("StartResolution: %d\n", startResolution);

	u3dGetU32(u3dcb->u3ddecoder, &endResolution);
	printf("EndResolution: %d\n", endResolution);
	
	U3DCompCtxID zero_ctx, 
		diffusecount_ctx, diffusecolorsign_ctx, colordiffr_ctx;
	u3dDecoderCreateCompCtx(u3dcb->u3ddecoder, &zero_ctx);
	u3dDecoderCreateCompCtx(u3dcb->u3ddecoder, &diffusecount_ctx);
	u3dDecoderCreateCompCtx(u3dcb->u3ddecoder, &diffusecolorsign_ctx);
	u3dDecoderCreateCompCtx(u3dcb->u3ddecoder, &colordiffr_ctx);

	for (U32 currentPosition = startResolution; 
			 currentPosition < endResolution;
			 currentPosition++) {
	  U32 splitPositionIndex;
	  if (currentPosition != 0) {
		u3dGetStaticCompressedU32(u3dcb->u3ddecoder,
									currentPosition, &splitPositionIndex);
	  } else {
		u3dGetDynamicCompressedU32(u3dcb->u3ddecoder,
									zero_ctx, &splitPositionIndex);
	  }

	  printf("  splitPositionIndex: %d\n", splitPositionIndex);

	  //return u3dStsNoErr;

	  // New Diffuse Color Info
      U16 newDiffuseColorCount;
	  u3dGetDynamicCompressedU16(u3dcb->u3ddecoder,
	  							diffusecount_ctx, &newDiffuseColorCount);
	  for (int i = 0; i < newDiffuseColorCount; i++) {
		U8 diffuseColorDifferenceSigns;
		u3dGetDynamicCompressedU8(u3dcb->u3ddecoder,
									diffusecolorsign_ctx, &diffuseColorDifferenceSigns);
		U32 diffuseColorDifferenceRed;
		u3dGetDynamicCompressedU32(u3dcb->u3ddecoder,
									colordiffr_ctx, &diffuseColorDifferenceRed);
	  }

	  // New Specular Color Info

	  // New Texture Coord Info


	  // New Face Count

	  // - New Face Position Info

	  // - Stay Or Move (Faces Using Split Position Count)

	  // - Move Face Info
	  
	  // New Face Info

	  // New Position Info

	  // - New Normal Info (Neighborhood Position Count)

	}

	return u3dStsNoErr;
} /* u3dDisposeInfo0xFFFFFF3C */


