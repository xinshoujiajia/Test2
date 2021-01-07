void Tower::Fire(Enemy* e)
{
  Vector2 dis=e->GetPosition()-GetPosition();
  float a=(e->GetMoveComponent()->GetVel()-Vel)
    *(e->GetMoveComponent()->GetVel()+Vel);
  float b=2.0f*e->GetMoveComponent()->GetVel();
    *Math::dot(dis,e->GetToward);
  float c=dis.LengthSq();
    
}
