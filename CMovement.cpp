#include "pch.h"
#include "CMovement.h"

#include "CTimeMgr.h"

#include "CObj.h"

CMovement::CMovement()
    : CComponent(ECOM_TYPE::MOVEMENT)
    , m_vCurForce()
    , m_vVelocity()
    , m_vGravityForce(Vec2(0.f, 600.f))
    , m_fSpeed(0.f)
    , m_fMass(1.f)
    , m_fMaxXSpeed(300.f)
    , m_fMaxYSpeed(300.f)
    , m_fFriction(500.f)
    , m_bGravityActive(false)
    , m_bGround(false)
{    
}

CMovement::~CMovement()
{
}


void CMovement::update()
{
    // 중력 체크
    if (m_bGravityActive && !m_bGround)
    {
        m_vCurForce += m_vGravityForce;
    }

    // 이번 프레임의 가속도 ( F = M * A )
    Vec2 vAccel = m_vCurForce / m_fMass;

    // 속도
    m_vVelocity += vAccel * DS;
    
    // 최대 속도 축별 제한
    if (m_fMaxXSpeed < abs(m_vVelocity.x))
    {
        m_vVelocity.x > 0 ? m_vVelocity.x = m_fMaxXSpeed : m_vVelocity.x = -m_fMaxXSpeed;
    }
        
    if (m_fMaxYSpeed < abs(m_vVelocity.y))
    {
        m_vVelocity.y > 0 ? m_vVelocity.y = m_fMaxYSpeed : m_vVelocity.y = -m_fMaxYSpeed;
    }


    // 마찰력 계산
    if (m_vCurForce.IsZero() && !m_vVelocity.IsZero())
    {
        Vec2 vFrictionDir = -m_vVelocity;
        vFrictionDir.Normalize();
        vFrictionDir *= m_fFriction;

        vFrictionDir /= m_fMass;
        vFrictionDir *= DS;

        // 마찰에 의해서 원래속도가 반대로 넘어가려는 경우는 정지한 것으로 본다.
        if (m_vVelocity.GetLength() < vFrictionDir.GetLength())
        {
            m_vVelocity = Vec2(0.f, 0.f);
        }        
        else
        {
            m_vVelocity += vFrictionDir;
        }
    }

    // 속도로 이동
    Vec2 vPos = GetOwner()->GetPos();
    vPos += m_vVelocity * DS;
    GetOwner()->SetPos(vPos);

    m_vCurForce = Vec2(0.f, 0.f);
}

void CMovement::OnGround()
{
    m_bGround = true;
    m_vVelocity.y = 0.f;

    //GetOwner()->OnGround();
}

void CMovement::OnAir()
{
    m_bGround = false;
}