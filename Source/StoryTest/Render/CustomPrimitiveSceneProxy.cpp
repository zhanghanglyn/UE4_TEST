// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomPrimitiveSceneProxy.h"

FCustomPrimitiveSceneProxy::FCustomPrimitiveSceneProxy(const UPrimitiveComponent* InComponent,
	FName ResourceName /* = NAME_None */) : FPrimitiveSceneProxy(InComponent, ResourceName)
{
	//m_VerTexFactory = new FCustomVertexFactory(ERHIFeatureLevel::SM4, "TestDraw!!!");
	SetVerTex();
}

void FCustomPrimitiveSceneProxy::SetVerTex()
{
	const float BoxSize = 50.0f;

	//��䶥��
	m_VertexBuffer.Vertices.Add(FVector(0.0f));
	m_VertexBuffer.Vertices.Add(FVector(BoxSize, 0.0f, 0.0f));
	m_VertexBuffer.Vertices.Add(FVector(0.0f, BoxSize, 0.0f));
	m_VertexBuffer.Vertices.Add(FVector(0.0f, 0.0f, BoxSize));

	//�������
	m_IndexBuffer.Indices.Add(0);
	m_IndexBuffer.Indices.Add(1);
	m_IndexBuffer.Indices.Add(2);

	m_IndexBuffer.Indices.Add(0);
	m_IndexBuffer.Indices.Add(1);
	m_IndexBuffer.Indices.Add(3);

	m_IndexBuffer.Indices.Add(0);
	m_IndexBuffer.Indices.Add(3);
	m_IndexBuffer.Indices.Add(2);

	m_IndexBuffer.Indices.Add(2);
	m_IndexBuffer.Indices.Add(3);
	m_IndexBuffer.Indices.Add(1);

	//��ʼ��
	m_VerTexFactory.Init(&m_VertexBuffer);
	BeginInitResource(&m_VertexBuffer);
	BeginInitResource(&m_IndexBuffer);
	BeginInitResource(&m_VerTexFactory);

}

/* ���ƾ�̬��Ⱦģ�� */
void FCustomPrimitiveSceneProxy::DrawStaticElements(FStaticPrimitiveDrawInterface* PDI)
{
	FMeshBatch Mesh;
	FMeshBatchElement& BatchElement = Mesh.Elements[0];
	BatchElement.IndexBuffer = &m_IndexBuffer;
	Mesh.bWireframe = false;
	Mesh.VertexFactory = &m_VerTexFactory;
	/* MD_Surface������������൱�ڼ���Ĭ�ϵ�3D��Ĳ��� */
	Mesh.MaterialRenderProxy = UMaterial::GetDefaultMaterial(MD_Surface)->GetRenderProxy();
	BatchElement.PrimitiveUniformBuffer = CreatePrimitiveUniformBufferImmediate(
		GetLocalToWorld(),GetBounds(),GetLocalBounds(), GetLocalBounds(),true,true
	);
	BatchElement.FirstIndex = 0;
	BatchElement.NumPrimitives = m_IndexBuffer.Indices.Num() / 3;
	BatchElement.MinVertexIndex = 0;
	BatchElement.MaxVertexIndex = m_IndexBuffer.Indices.Num() / 3 - 1;
	Mesh.ReverseCulling = IsLocalToWorldDeterminantNegative();
	Mesh.Type = PT_TriangleList;
	Mesh.DepthPriorityGroup = SDPG_Foreground;
	Mesh.bCanApplyViewModeOverrides = false;
	Mesh.bDisableBackfaceCulling = false;
	PDI->DrawMesh(Mesh , 1.0f);

}






/* �Զ��嶥�㻺����� */
void FCustomVertexBuffer::InitRHI()
{
	FRHIResourceCreateInfo CreateInfo;
	void* LockedData = nullptr;
	VertexBufferRHI = RHICreateAndLockVertexBuffer(Vertices.Num() * sizeof(FDynamicMeshVertex),
		BUF_Static , CreateInfo, LockedData);

	FMemory::Memcmp(LockedData, Vertices.GetData(), Vertices.Num() * sizeof(FDynamicMeshVertex));
	RHIUnlockVertexBuffer(VertexBufferRHI);
}

/* �Զ�������������� */
void FCustomIndexBuffer::InitRHI()
{
	FRHIResourceCreateInfo CreateInfo;
	void* LockedData = nullptr;
	IndexBufferRHI = RHICreateIndexBuffer(sizeof(int32), Indices.Num() * sizeof(int32),
		BUF_Static, CreateInfo);
	void* Buffer = RHILockIndexBuffer(IndexBufferRHI, 0, sizeof(int32), RLM_WriteOnly);

	FMemory::Memcmp(LockedData, Indices.GetData(), Indices.Num() * sizeof(int32));
	RHIUnlockIndexBuffer(IndexBufferRHI);

}