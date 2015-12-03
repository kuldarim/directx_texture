////////////////////////////////////////////////////////////////////////////////
// Filename: plane_modelclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "plane_modelclass.h"


PlaneModelClass::PlaneModelClass():IndexModelClass()
{
	m_Material.ambientColor = D3DXVECTOR4( 0.1f, 0.2f, 0.1f, 1.0f );
	m_Material.diffuseColor = D3DXVECTOR4( 0.0f, 1.0f, 0.0f, 1.0f );
	m_Material.specularColor = D3DXVECTOR4( 1.0f, 1.0f, 1.0f, 25.0f );
}


PlaneModelClass::PlaneModelClass(const PlaneModelClass& other)
{
}


PlaneModelClass::~PlaneModelClass()
{
}

MaterialBufferType PlaneModelClass::getMaterial()
{
	return m_Material;
}

bool PlaneModelClass::InitializeBuffers(ID3D11Device* device)
{
	HRESULT result;
//
//	Set parameters of the plain
//
	const UINT ndim = 200;

	const float yval =  -0.50f;
	const float xmin = -120.0f;
	const float xmax =  120.0f;
	const float zmin = -120.0f;
	const float zmax =  120.0f;

	float dx= (xmax-xmin)/float(ndim);
	float dz= (zmax-zmin)/float(ndim);
//
// Process the vertex buffer
//
	VertexNorm* vertices;
	D3D11_BUFFER_DESC vertexBufferDesc;
    D3D11_SUBRESOURCE_DATA vertexData;

	// Set the number of vertices in the vertex array.
	int vCount = (ndim+1)*(ndim+1);
	SetVertexCount(vCount);

	// Create the vertex array.
	vertices = new VertexNorm[vCount];
	if(!vertices)
	{
		return false;
	}

	//for( UINT iz=0; iz < vCount ; iz++ )
	//	vertices[iz].color = D3DXVECTOR4(0.0f, 0.5f, 0.0f, 1.0f);

	// Load the vertex array with data.
	vertices[0].position = D3DXVECTOR3(xmin, yval, zmin);
	vertices[0].normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	for( UINT iz=0; iz<=ndim ; iz++ )
	{
		if(iz == 0)
		{
			vertices[0 + iz*(ndim+1)].position.z = zmin;
		}
		else
		{
			vertices[0 + iz*(ndim+1)].position.z = vertices[0 + (iz-1)*(ndim+1)].position.z + dz;
		}
		vertices[0 + iz*(ndim+1)].position.x = xmin;
		vertices[0 + iz*(ndim+1)].position.y = yval;
		vertices[0 + iz*(ndim+1)].normal  =D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		for( UINT ix=1 ; ix<=ndim ; ix++ )
		{
			vertices[ix + iz*(ndim+1)].position.x = vertices[ix-1 + iz*(ndim+1)].position.x + dx;
			vertices[ix + iz*(ndim+1)].position.y = yval;
			vertices[ix + iz*(ndim+1)].position.z = vertices[0 + iz*(ndim+1)].position.z ;
			vertices[ix + iz*(ndim+1)].normal  =D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		}
	}

	// Set up the description of the static vertex buffer.
    vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    vertexBufferDesc.ByteWidth = sizeof(VertexNorm) * vCount;
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertexBufferDesc.CPUAccessFlags = 0;
    vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the vertex data.
	ZeroMemory( &vertexData, sizeof( vertexData ) );
    vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0; 

	// Now create the vertex buffer.
    result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if(FAILED(result))
	{
		return false;
	}

	// Release the array now that the vertex buffer has been created and loaded.
	delete [] vertices;
	vertices = 0;

//
//Process the index buffer	
//
	unsigned long* indices;
	D3D11_BUFFER_DESC indexBufferDesc;
	D3D11_SUBRESOURCE_DATA indexData;

	// Set the number of indices in the index array.
	int iCount = ndim*ndim*2*3;
	SetIndexCount(iCount);

	// Create the index array.
	indices = new unsigned long[iCount];
	if(!indices)
	{
		return false;
	}
	// Load the index array with data.
	for( UINT iz=0 ; iz<ndim ; iz++ )
	{
		for( UINT ix=0 ; ix<ndim ; ix++ )
		{
			indices[0 + ix*6 + iz*6*ndim] = ix+0 + iz*(ndim+1) ;
			indices[1 + ix*6 + iz*6*ndim] = ix+1 + iz*(ndim+1) ;
			indices[2 + ix*6 + iz*6*ndim] = ix+0 + iz*(ndim+1) + (ndim+1) ;

			indices[3 + ix*6 + iz*6*ndim] = ix+1 + iz*(ndim+1) ;
			indices[4 + ix*6 + iz*6*ndim] = ix+1 + iz*(ndim+1) + (ndim+1) ;
			indices[5 + ix*6 + iz*6*ndim] = ix+0 + iz*(ndim+1) + (ndim+1);
		}
	}

	// Set up the description of the static index buffer.
    indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    indexBufferDesc.ByteWidth = sizeof(unsigned long) * iCount;
    indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    indexBufferDesc.CPUAccessFlags = 0;
    indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the index data.
    indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if(FAILED(result))
	{
		return false;
	}

	// Release the array now that the vertex buffer has been created and loaded.
	delete [] indices;
	indices = 0;

	return true;
}


void PlaneModelClass::Render(ID3D11DeviceContext* deviceContext)
{
	//Update the world transformations
	D3DXMATRIX temp;
	D3DXMatrixIdentity(&temp);
	SetModelWorldMatrix(temp);

	// Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
	RenderBuffers(deviceContext);

	return;
}

void PlaneModelClass::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	unsigned int stride;
	unsigned int offset;

	// Set vertex buffer stride and offset.
	stride = sizeof(VertexNorm); 
	offset = 0;
    
	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

    // Set the index buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

    // Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// Render indexed primitives
	deviceContext->DrawIndexed(GetIndexCount(), 0, 0);

	return;
}