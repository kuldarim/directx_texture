////////////////////////////////////////////////////////////////////////////////
// Filename: Sphere_modelclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "sphere_modelclass.h"

static inline void sincosf( float angle, float* psin, float* pcos )
{
    *psin = sinf( angle );
    *pcos = cosf( angle );
}

SphereModelClass::SphereModelClass():IndexModelClass()
{
	m_Material.ambientColor = D3DXVECTOR4( 0.125f, 0.05f, 0.05f, 1.0f );
	m_Material.diffuseColor = D3DXVECTOR4( 1.0f, 0.0f, 0.0f, 1.0f );
	m_Material.specularColor = D3DXVECTOR4( 1.0f, 1.0f, 1.0f, 25.0f );
}


SphereModelClass::SphereModelClass(const SphereModelClass& other)
{
}


SphereModelClass::~SphereModelClass()
{
}

MaterialBufferType SphereModelClass::getMaterial()
{
	return m_Material;
}

bool SphereModelClass::InitializeBuffers(ID3D11Device* device)
{
	HRESULT result;
//
// Set parameters of the sphere.
//
	float fRadius = 1.0f;
	UINT uSlices = 32;
	UINT uStacks = 32;
	if( uSlices > CACHE_SIZE )
        uSlices = CACHE_SIZE;
    if( uStacks > CACHE_SIZE )
        uStacks = CACHE_SIZE;
//
// Process buffers
//
	// Vertex buffer
	VertexNorm* vertices;
	D3D11_BUFFER_DESC vertexBufferDesc;
    D3D11_SUBRESOURCE_DATA vertexData;

	// Set vertex count
	int vCount = ( uStacks - 1 ) * uSlices + 2;
	SetVertexCount(vCount);

	// Create the vertex array.
	vertices = new VertexNorm[vCount];
	if(!vertices)
	{
		return false;
	}

	// Index buffer
	unsigned long* indices;
	D3D11_BUFFER_DESC indexBufferDesc;
	D3D11_SUBRESOURCE_DATA indexData;

	// Set the number of indices in the index array.
	int iCount = 6 * ( uStacks - 1 ) * uSlices;
	SetIndexCount(iCount);

	// Create the index array.
	indices = new unsigned long[iCount];
	if(!indices)
	{
		return false;
	}

    // Create a sphere
    MakeSphere( vertices, indices, fRadius, uSlices, uStacks );

	//for( UINT iz=0; iz < vCount ; iz++ )
	//	vertices[iz].color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);

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


void SphereModelClass::Render(ID3D11DeviceContext* deviceContext)
{
	//Update the world transformations
	D3DXMATRIX transMatrix, scaleMatrix;
	D3DXMatrixTranslation(&transMatrix, -1.0f,1.0f,0.0f);
	
	SetModelWorldMatrix(transMatrix);
	// Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
	RenderBuffers(deviceContext);

	return;
}


void SphereModelClass::RenderBuffers(ID3D11DeviceContext* deviceContext)
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

    // Set the type of primitive that should be rendered from this vertex buffer, in this case Spheres.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// render primitives
	deviceContext->DrawIndexed(GetIndexCount(), 0, 0);

	return;
}

void SphereModelClass::MakeSphere( VertexNorm* pVertices, unsigned long* pwIndices, float fRadius, UINT uSlices, UINT uStacks )
{
    UINT i, j;

    // Sin/Cos caches
    float sinI[CACHE_SIZE], cosI[CACHE_SIZE];
    float sinJ[CACHE_SIZE], cosJ[CACHE_SIZE];

    for( i = 0; i < uSlices; i++ )
        sincosf( 2.0f * D3DX_PI * i / uSlices, sinI + i, cosI + i );

    for( j = 0; j < uStacks; j++ )
        sincosf( D3DX_PI * j / uStacks, sinJ + j, cosJ + j );



    // Generate vertices
    VertexNorm* pVertex = pVertices;

    // +Z pole
    pVertex->position = D3DXVECTOR3( 0.0f, 0.0f, fRadius );
    pVertex->normal = D3DXVECTOR3( 0.0f, 0.0f, 1.0f );
    pVertex++;

    // Stacks
    for( j = 1; j < uStacks; j++ )
    {
        for( i = 0; i < uSlices; i++ )
        {
            D3DXVECTOR3 norm( sinI[i]* sinJ[j], cosI[i]* sinJ[j], cosJ[j] );

            pVertex->position = norm * fRadius;
            pVertex->normal = norm;

            pVertex++;
        }
    }

    // Z- pole
    pVertex->position = D3DXVECTOR3( 0.0f, 0.0f, -fRadius );
    pVertex->normal = D3DXVECTOR3( 0.0f, 0.0f, -1.0f );
    pVertex++;



    // Generate indices
    unsigned long* pwFace = pwIndices;
    UINT uRowA, uRowB;

    // Z+ pole
    uRowA = 0;
    uRowB = 1;

    for( i = 0; i < uSlices - 1; i++ )
    {
        pwFace[0] = ( WORD )( uRowA );
        pwFace[1] = ( WORD )( uRowB + i + 1 );
        pwFace[2] = ( WORD )( uRowB + i );
        pwFace += 3;
    }

    pwFace[0] = ( WORD )( uRowA );
    pwFace[1] = ( WORD )( uRowB );
    pwFace[2] = ( WORD )( uRowB + i );
    pwFace += 3;

    // Interior stacks
    for( j = 1; j < uStacks - 1; j++ )
    {
        uRowA = 1 + ( j - 1 ) * uSlices;
        uRowB = uRowA + uSlices;

        for( i = 0; i < uSlices - 1; i++ )
        {
            pwFace[0] = ( WORD )( uRowA + i );
            pwFace[1] = ( WORD )( uRowA + i + 1 );
            pwFace[2] = ( WORD )( uRowB + i );
            pwFace += 3;

            pwFace[0] = ( WORD )( uRowA + i + 1 );
            pwFace[1] = ( WORD )( uRowB + i + 1 );
            pwFace[2] = ( WORD )( uRowB + i );
            pwFace += 3;
        }

        pwFace[0] = ( WORD )( uRowA + i );
        pwFace[1] = ( WORD )( uRowA );
        pwFace[2] = ( WORD )( uRowB + i );
        pwFace += 3;

        pwFace[0] = ( WORD )( uRowA );
        pwFace[1] = ( WORD )( uRowB );
        pwFace[2] = ( WORD )( uRowB + i );
        pwFace += 3;
    }

    // Z- pole
    uRowA = 1 + ( uStacks - 2 ) * uSlices;
    uRowB = uRowA + uSlices;

    for( i = 0; i < uSlices - 1; i++ )
    {
        pwFace[0] = ( WORD )( uRowA + i );
        pwFace[1] = ( WORD )( uRowA + i + 1 );
        pwFace[2] = ( WORD )( uRowB );
        pwFace += 3;
    }

    pwFace[0] = ( WORD )( uRowA + i );
    pwFace[1] = ( WORD )( uRowA );
    pwFace[2] = ( WORD )( uRowB );
    pwFace += 3;
}
/*

static const D3D10_INPUT_ELEMENT_DESC s_ShapeLayout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0 },
        { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D10_INPUT_PER_VERTEX_DATA, 0 },
    };


//--------------------------------------------------------------------------------------

*/