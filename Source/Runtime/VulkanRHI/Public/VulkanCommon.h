// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

/*=============================================================================
	VulkanCommon.h: Common definitions used for both runtime and compiling shaders.
=============================================================================*/

#pragma once

#include "RHIDefinitions.h"

namespace DescriptorSet
{
	enum EStage
	{
		// Adjusting these requires a full shader rebuild (ie modify the guid on VulkanCommon.usf)
		// Keep the values in sync with EShaderFrequency
		Vertex			= 0,
		Pixel			= 1,
		Geometry		= 2,
		//Hull			= 3,
		//Domain			= 4,

		// We don't support tessellation on desktop currently
		NumGfxStages	= 3,

		// Mobile only supports VS + PS currently
		NumMobileStages = 2,

		// Compute is its own pipeline, so it can all live as set 0
		Compute			= 0,

		Invalid			= -1,
	};

	inline EStage GetSetForFrequency(EShaderFrequency Stage)
	{
		switch (Stage)
		{
		case SF_Vertex:		return Vertex;
		//case SF_Hull:		return Hull;
		//case SF_Domain:		return Domain;
		case SF_Pixel:		return Pixel;
		case SF_Geometry:	return Geometry;
		case SF_Compute:	return Compute;
		default:
			checkf(0, TEXT("Invalid shader Stage %d"), (int32)Stage);
			break;
		}

		return Invalid;
	}

	inline EShaderFrequency GetFrequencyForGfxSet(EStage Stage)
	{
		switch (Stage)
		{
		case EStage::Vertex:	return SF_Vertex;
		//case EStage::Hull:		return SF_Hull;
		//case EStage::Domain:	return SF_Domain;
		case EStage::Pixel:		return SF_Pixel;
		case EStage::Geometry:	return SF_Geometry;
		default:
			checkf(0, TEXT("Invalid shader Stage %d"), (int32)Stage);
			break;
		}

		return SF_NumFrequencies;
	}
};

namespace EVulkanBindingType
{
	enum EType : uint8
	{
		PackedUniformBuffer,	//VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER
		UniformBuffer,			//VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER

		CombinedImageSampler,	//VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER
		Sampler,				//VK_DESCRIPTOR_TYPE_SAMPLER
		Image,					//VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE

		UniformTexelBuffer,		//VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER	Buffer<>

		//A storage image (VK_DESCRIPTOR_TYPE_STORAGE_IMAGE) is a descriptor type that is used for load, store, and atomic operations on image memory from within shaders bound to pipelines.
		StorageImage,				//VK_DESCRIPTOR_TYPE_STORAGE_IMAGE		RWTexture

		//RWBuffer/RWTexture?
		//A storage texel buffer (VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER) represents a tightly packed array of homogeneous formatted data that is stored in a buffer and is made accessible to shaders. Storage texel buffers differ from uniform texel buffers in that they support stores and atomic operations in shaders, may support a different maximum length, and may have different performance characteristics.
		StorageTexelBuffer,

		// UAV/RWBuffer
		//A storage buffer(VK_DESCRIPTOR_TYPE_STORAGE_BUFFER) is a region of structured storage that supports both read and write access for shaders.In addition to general read and write operations, some members of storage buffers can be used as the target of atomic operations.In general, atomic operations are only supported on members that have unsigned integer formats.
		StorageBuffer,


		Count,
	};

	static inline char GetBindingTypeChar(EType Type)
	{
		// Make sure these do NOT alias EPackedTypeName*
		switch (Type)
		{
		case UniformBuffer:			return 'b';
		case CombinedImageSampler:	return 'c';
		case Sampler:				return 'p';
		case Image:					return 'w';
		case UniformTexelBuffer:	return 'x';
		case StorageImage:			return 'y';
		case StorageTexelBuffer:	return 'z';
		case StorageBuffer:			return 'v';
		default:
			check(0);
			break;
		}

		return 0;
	}
}

/** How many back buffers to cycle through */
enum
{
	NUM_RENDER_BUFFERS = 3,
};
