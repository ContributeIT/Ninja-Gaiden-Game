#include "Player.h"
#include "Game.h"


Player * Player::instance = NULL;
Player * Player::getInstance()
{
	if (instance == NULL)
		instance = new Player();
	return instance;
}

Player::Player()
{
	resetAllStats();
	hasItem = false;
	isExist = true;
	isStopDrawing = false;
	item = new UsableItem();
}


Player::~Player()
{
}

void Player::setMinClimbHeight(float minClimbHeight)
{
	this->minClimbHeight = minClimbHeight + DEFAULT_HEIGHT;
}

void Player::setMaxClimbHeight(float maxClimbHeight)
{
	this->maxClimbHeight = maxClimbHeight;
}

void Player::InitPlayer(float x, float y)
{
	started = false;
	SetStatus(PLAYER_NULL);
	SetStatus(PLAYER_STANDING);
	setX(x);
	setY(y + getHeight());
	setVelX(DEFAULT_VELOCITY_X);
	setVelY(DEFAULT_VELOCITY_Y);

	minHeight = getY();
	maxHeight = minHeight + DEFAULT_JUMP_HEIGHT;

	isMovable = true;
	isMoving = directionChanged = startAnimation = isJumping = false;
	isOnGround = true;

	isInvincible = false;
	isKnockback = false;

	isDead = false;
	isStopDrawing = false;

	X_moved = false;
}

void Player::setMinJumpHeight(float minHeight)
{
	this->minHeight = minHeight + DEFAULT_HEIGHT;
}

void Player::setMaxJumpHeight(float maxHeight)
{
	this->maxHeight = maxHeight;
}

void Player::SetStatus(PLAYER_STATUS status, int direction)
{
	if (this->status != status || directionChanged)
	{
		PLAYER_STATUS temp = this->status;
		this->status = status;
		directionX = direction;

		switch (status)
		{
		case PLAYER_STANDING:
			#pragma region Show code
			startAnimation = false;
			setSize(22, 32);
			realWidth = 20;
			sprite->SetAnimation(getWidth(), getHeight(), 1, 1, 0, 0);
			if (direction > 0)
			{
				sprite->Release();
				sprite->LoadTexture("images/Ryu_right.png", D3DCOLOR_XRGB(255, 0, 255));
			}
			else
			{
				sprite->Release();
				sprite->LoadTexture("images/Ryu_left.png", D3DCOLOR_XRGB(255, 0, 255));
			}
			break;
#pragma endregion
		case PLAYER_MOVING:
			#pragma region Show code
			SetStatus(PLAYER_STANDING, direction);
			this->status = PLAYER_MOVING;
			startAnimation = true;
			sprite->SetAnimation(getWidth(), getHeight(), 4, 4, 1, 3);
			break;
#pragma endregion
		case PLAYER_JUMPING:
			#pragma region Show code
			if (isClimbing) isClimbing = false;
			isJumping = true;

			startAnimation = true;
			setSize(24, 24);
			realWidth = 24;
			sprite->SetAnimation(getWidth(), getHeight(), 4, 2, 0, 3);
			if (direction > 0)
			{
				sprite->Release();
				sprite->LoadTexture("images/Ryu_jump_right.png", D3DCOLOR_XRGB(255, 0, 255));
			}
			else
			{
				sprite->Release();
				sprite->LoadTexture("images/Ryu_jump_left.png", D3DCOLOR_XRGB(255, 0, 255));
			}
			break;
#pragma endregion
		case PLAYER_END_JUMPING:
			#pragma region Show code
			isJumping = false;
			setY(getY() + 8);
			SetStatus(PLAYER_STANDING, direction);
			break;
#pragma endregion
		case PLAYER_KNOCKBACK:
			#pragma region Show code
			isKnockback = true;
			isMovable = false;
			isMoving = false;
			isClimbing = false;
			isJumping = false;
			isOnGround = true;
			startKnockback = GetTickCount();
			directionY = 1;
			// trở nên bất tử
			SetStatus(PLAYER_INVINCIBLE, direction);

			setSize(24, 24);
			realWidth = 24;
			sprite->SetAnimation(getWidth(), getHeight(), 1, 1, 0, 0);
			if (direction > 0)
			{
				sprite->Release();
				sprite->LoadTexture("images/Ryu_jump_right.png", D3DCOLOR_XRGB(255, 0, 255));
			}
			else
			{
				sprite->Release();
				sprite->LoadTexture("images/Ryu_jump_left.png", D3DCOLOR_XRGB(255, 0, 255));
			}
			this->status = temp;
			break;
#pragma endregion
		case PLAYER_INVINCIBLE:
			#pragma region Show code
			isInvincible = true;
			startInvincible = GetTickCount();
			this->status = temp;
			break;
#pragma endregion
		case PLAYER_ATTACK:
			#pragma region Show code
			if (!isJumping && isOnGround) isMovable = false;
			if (!isAttacking) startAttack = GetTickCount();
			if (!isAttacking) isAttacking = true;
			
			startAnimation = true;
			setSize(40, 32);
			realWidth = 20;
			sprite->SetAnimation(getWidth(), getHeight(), 3, 3, 0, 2);
			sprite->setCurrentAnimation(0);
			if (direction > 0)
			{
				if (X_moved)
				{
					moveX(16);
					X_moved = false;
				}
				sprite->Release();
				sprite->LoadTexture("images/Ryu_attack_right.png", D3DCOLOR_XRGB(255, 163, 177));
			}
			else
			{
				if (!X_moved)
				{
					moveX(-16);
					X_moved = true;
				}
				sprite->Release();
				sprite->LoadTexture("images/Ryu_attack_left.png", D3DCOLOR_XRGB(255, 163, 177));
			}
			break;
#pragma endregion
		case PLAYER_JUMP_ATTACK:
			#pragma region Show code
			if (!isAttacking) startAttack = GetTickCount();
			isAttacking = true;

			startAnimation = true;
			setSize(32, 32);
			realWidth = 24;
			sprite->SetAnimation(getWidth(), getHeight(), 4, 2, 0, 3);
			if (direction > 0)
			{
				sprite->Release();
				sprite->LoadTexture("images/Ryu_jump_attack_right.png", D3DCOLOR_XRGB(255, 163, 177));
			}
			else
			{
				sprite->Release();
				sprite->LoadTexture("images/Ryu_jump_attack_left.png", D3DCOLOR_XRGB(255, 163, 177));
			}
			break;
#pragma endregion
		case PLAYER_CLINGING:
			#pragma region Show code
			isClimbing = true;
			if (isMoving) isMoving = false;
			if (isJumping) isJumping = false;
			if (!isOnGround) isOnGround = true;
			if (isAttacking) isAttacking = false;

			startAnimation = false;
			setSize(16, 32);
			realWidth = 16;
			sprite->SetAnimation(getWidth(), getHeight(), 1, 1, 0, 0);
			if (direction > 0)
			{
				sprite->Release();
				sprite->LoadTexture("images/Ryu_climb_right.png", D3DCOLOR_XRGB(255, 163, 177));
			}
			else
			{
				sprite->Release();
				sprite->LoadTexture("images/Ryu_climb_left.png", D3DCOLOR_XRGB(255, 163, 177));
			}
			break;
#pragma endregion
		case PLAYER_CLIMBING:
			#pragma region Show code
			setVelY(DEFAULT_CLIMB_VELOCITY * directionY);
			SetStatus(PLAYER_CLINGING, directionX);
			this->status = PLAYER_CLIMBING;
			startAnimation = true;
			sprite->SetAnimation(getWidth(), getHeight(), 2, 2, 0, 1);
			break;
#pragma endregion
		case PLAYER_ITEM_USE:
			#pragma region Show code
			if (!isJumping && isOnGround) isMovable = false;
			if (!isThrowing) startThrowing = GetTickCount();
			isThrowing = true;

			startAnimation = true;
			setSize(28, 32);
			realWidth = 20;
			sprite->SetAnimation(getWidth(), getHeight(), 1, 1, 0, 0);
			if (direction > 0)
			{
				sprite->Release();
				sprite->LoadTexture("images/Ryu_throwing_right.png", D3DCOLOR_XRGB(255, 163, 177));
			}
			else
			{
				sprite->Release();
				sprite->LoadTexture("images/Ryu_throwing_left.png", D3DCOLOR_XRGB(255, 163, 177));
			}
			break;
#pragma endregion
		case PLAYER_DIE:
			isDead = true;
			break;
		default:
			break;
		}
	}
}

void Player::Update(DWORD dt)
{
	timer.tickPerAnim = dt;

	#pragma region mapStart, mapEnd, cameraX, cameraWidth
	Camera * camera = Camera::getInstance();
	int mapStart = Stage::getInstance()->getMapStart();
	int mapEnd = Stage::getInstance()->getMapEnd();
	float cameraX = camera->getX();
	float cameraWidth = camera->getWidth();
#pragma endregion Lấy giới hạn map và camera

	// Chỉ xử lý các trạng thái chủ động khi không bị knockback
	if (!isKnockback)
	{
		// lên xuống qua lại
		if (directionChanged)
		{
			SetStatus(this->status, directionX);
			directionChanged = false;
		}

		// Xử lý di chuyển
		if (isMovable)	// chủ yếu để ép player đứng yên khi đánh lúc đang đứng
		{
			if (isMoving)
			{
				if (!isClimbing)
				{
					selfMovingX();
				}
			}
		}

		#pragma region Nhảy
		if (isJumping)
		{
			// Tăng giảm độ cao
			if (directionY > 0)
			{
				setVelY(DEFAULT_VELOCITY_Y);
				selfMovingY();
			}

			// Nhảy lên điểm cao nhất thì ngưng
			if ((!isAttacking && getY() >= maxHeight) ||
				(isAttacking && getY() >= maxHeight + getWidth() - getRealWidth()))
			{
				directionY = -1;
				isOnGround = false;
			}

			if (getY() <= minHeight)
			{
				isJumping = false;
				SetStatus(PLAYER_MOVING, directionX);
			}
		}
#pragma endregion Xử lý nhảy

		#pragma region Leo trèo
		if (isClimbing)
		{
			if (isMoving)
			{
				if (getY() <= maxClimbHeight && getY() >= minClimbHeight)
					selfMovingY();

				if (getY() > maxClimbHeight)
					setY(maxClimbHeight);
				if (getY() < minClimbHeight)
					setY(minClimbHeight);
			}
		}
#pragma endregion Xử lý leo trèo

		#pragma region Tấn công
		if (isAttacking)
		{
			// Khi đứng
			if (isOnGround && !isJumping && !isClimbing)
			{
				timer.tickPerAnim = (DWORD) ATTACK_TIME / 3;

				if (GetTickCount() - startAttack >= ATTACK_TIME)
				{
					isAttacking = false;
					isMovable = true;
					if (X_moved)
					{
						moveX(16);
						X_moved = false;
					}
					SetStatus(PLAYER_STANDING, directionX);
				}		
			}
			// Khi trên không
			else
			{
				if (GetTickCount() - startAttack >= ATTACK_TIME || (isOnGround && !isJumping))
				{
					isAttacking = false;

					if (isOnGround && !isJumping)
					{
						SetStatus(PLAYER_MOVING, directionX);
					}
					else
					{
						SetStatus(PLAYER_JUMPING, directionX);
					}
				}
			}
		}
#pragma endregion Xử lý tấn công

		#pragma region Dùng item
		if (isThrowing)
		{
			timer.tickPerAnim = (DWORD)THROWING_TIME / 2;

			if (GetTickCount() - startThrowing >= THROWING_TIME)
			{
				isThrowing = false;
				isMovable = true;
				if (isMoving)
				{
					SetStatus(PLAYER_MOVING, directionX);
				}
				else
				{
					SetStatus(PLAYER_STANDING, directionX);
				}
			}
			else
			{
				SetStatus(PLAYER_ITEM_USE, directionX);
			}
		}
#pragma endregion Xử lý ném phi tiêu

	}
	// Xử lý khi bị knockback	[incompleted]
	else
	{
		// knockback trong khoảng thời gian KNOCKBACK_TIME
		if (GetTickCount() - startKnockback >= KNOCKBACK_TIME)
		{
			isKnockback = false;
			isMovable = true;
			SetStatus(PLAYER_NULL, directionX);
			SetStatus(PLAYER_STANDING, directionX);
		}
		else
		{
			// trường hợp đặc biệt ^_^ phải ép kết thúc tấn công trước khi knockback
			if (isAttacking && directionX == -1)
			{
				isAttacking = false;
				isMovable = true;
				if (X_moved)
				{
					moveX(16);
					X_moved = false;
				}
				SetStatus(PLAYER_STANDING, directionX);
			}

			moveX(-DEFAULT_VELOCITY_X * directionX);

			if (directionY > 0)
			{
				moveY(DEFAULT_VELOCITY_Y * 1.4f);
			}
			if (getY() > (maxHeight + minHeight) / 2)
			{
				directionY = -1;
			}
		}
	}

	// Update item
	//	init item
	if (item->isUsed)
	{
		item->directionX = directionX;
		if (directionX > 0)
		{
			item->Init(getRight(), getTop() - 8 + item->getHeight() / 2);
		}
		else
		{
			item->Init(getLeft() - item->getWidth(), getTop() - 8 + item->getHeight() / 2);
		}
	}
	//	draw item
	if (item->isExist)
	{
		item->Update();
	}

	// ?
	if (!isJumpable)
	{
		if (GetTickCount() - startCooldownJump >= COOLDOWN_JUMP)
		{
			isJumpable = true;
		}
	}

	// Invincible
	if (isInvincible)
	{
		// làm hiệu ứng chớp chớp
		if (GetTickCount() - stopDrawing >= BLINK_DELAY)
		{
			isStopDrawing = !isStopDrawing;
		}

		// Chỉ bất tử trong khoảng thời gian INVINCIBLE_TIME
		if (GetTickCount() - startInvincible >= INVINCIBLE_TIME)
		{
			isInvincible = false;
			isStopDrawing = false;
		}
	}

	// Gravity: nhân vật rớt xuống khi không đứng trên mặt đất chạm đất
	if (!isOnGround)
	{
		moveY(-DEFAULT_VELOCITY_Y);
	}
	// Kiểm tra xem nhân vật có đang đứng trên mặt đất hay không
	if (!isJumping && !isClimbing && getY() > minHeight
		&& !(isOnGround && isAttacking))
	{
		isOnGround = false;
	}
	else if (getY() <= minHeight)
	{
		if (getY() < minHeight)
			setY(minHeight);
		isOnGround = true;
		isJumping = false;
	}


	// Update camera theo vị trí nhân vật
	if (getMidX() > mapStart + cameraWidth / 2 &&
		getMidX() < mapEnd - cameraWidth / 2 && 
		(status != PLAYER_ATTACK))
	{
		camera->trackPlayer(this);
	}
	// Kiểm tra giới hạn di chuyển
	// giới hạn nhân vật trong map
	if (started)
	if (this->getRight() - this->getRealWidth() < mapStart && this->getRight() > mapStart)
	{
		this->setX(mapStart - this->getWidth() + this->getRealWidth());
	}
	// giới hạn camera trong map
	if (cameraX < mapStart)
	{
		camera->setX(mapStart);
	}
	if (cameraX > mapEnd - cameraWidth)
	{
		camera->setX(mapEnd - cameraWidth);
	}

	// Vẽ lên camera
	if (!isStopDrawing)
		Draw();

	if (HP <= 0)
	{
		SetStatus(PLAYER_DIE);
		isOnGround = true;
	}

	// Chết thì làm sao
	if (isDead)
	{
		isDead = false;
		// thêm điều kiện nếu còn mạng thì mới sống lại đc
		if (isOnGround)	// té
		{
			Stage::getInstance()->Release();
			Game::getInstance()->InitGame();
			
			// Chưa làm kỹ
			HP = MAX_HP;
			life -= 1;

			
		}
	}

	if (life < 0)
	{
		resetAllStats();
	}
}

#pragma region Stats
void Player::setScore(int score)
{
	this->score = score;
}

void Player::setHP(int HP)
{
	this->HP = HP;

	if (this->HP > MAX_HP)
	{
		setHP(MAX_HP);
	}
}

void Player::setLife(int life)
{
	this->life = life;
}

void Player::setSpiritualStrength(int spiritualStr)
{
	this->spiritualStr = spiritualStr;

	if (this->HP > MAX_SPIRITUAL_STRENGTH_PTS)
	{
		setHP(MAX_SPIRITUAL_STRENGTH_PTS);
	}
}

void Player::addScore(int score)
{
	this->score += score;
}

void Player::increase_HP(int HP)
{
	this->HP += HP;

	if (this->HP > MAX_HP)
	{
		setHP(MAX_HP);
	}
}

void Player::decrease_HP(int HP)
{
	this->HP -= HP;
}

void Player::increase_life(int life)
{
	this->life += life;
}

void Player::decrease_life(int life)
{
	this->life -= life;
}

void Player::increase_spiritualStrength(int ss)
{
	this->spiritualStr += ss;

	if (this->HP > MAX_SPIRITUAL_STRENGTH_PTS)
	{
		setHP(MAX_SPIRITUAL_STRENGTH_PTS);
	}
}

void Player::decrease_spiritualStrength(int ss)
{
	this->spiritualStr -= ss;
}
#pragma endregion get/set Score, HP, life, Spiritual strength

void Player::setItem(UsableItem * item)
{
	if (!hasItem)
	{
		hasItem = true;
	}
	delete this->item;
	this->item = item;
}

void Player::resetAllStats()
{
	HP = MAX_HP;
	life = 2;	// ?
	score = 0;
	spiritualStr = 0;	// ?
	//if (hasItem)
	{
		//delete item;
		hasItem = false;
	}
}