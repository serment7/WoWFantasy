
#pragma once

class cBone : public D3DXFRAME
{
private:
	D3DXMATRIX ConbinedTransformActionMatrix;

public:

	void SetConbinedTransformActionMatrix( const D3DXMATRIX& mat ) 
	{
		ConbinedTransformActionMatrix = mat;
	}

	const D3DXMATRIX& GetConbinedTransformActionMatrix()
	{
		return ConBinedTransformActionMatrix;
	}
};

class cBoneMesh : public D3DXMESHCONTAINER
{
public:
	std::vector<
};

class cAllocateHierarchy : public ID3DXAllocateHierarchy
{
public:
	cAllocateHierarchy();
	virtual ~cAllocateHierarchy();

};
