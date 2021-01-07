void Tower::Fire(Enemy* e)
{
  Vector2 dis=e->GetPosition()-GetPosition();
  float a=(e->GetMoveComponent()->GetVel()-Vel)
    *(e->GetMoveComponent()->GetVel()+Vel);
  float b=2.0f*e->GetMoveComponent()->GetVel();
    *Math::dot(dis,e->GetToward);
  float c=dis.LengthSq();
  float t;
  float disc=b*b-4.0f*a*c;
  if(disc>0.0f)
  {
    disc=Math::Sqrt(disc);
    t=(-b-disc)/(2.0f*a);
    if(t>0.0f)
    {
      Vector2 toward=dis+e->GetToward()*t*e->GetMoveComponent()->GetVel();
      toward.Normlize();
      Bullet* bullet=new Bullet(GetGame());
      bullet->SetToward(toward);
      bullet->SetVel(vel);
      bullet->SetLife(t);
    }
  }
}
